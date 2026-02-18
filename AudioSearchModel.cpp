#include "AudioSearchModel.h"
#include "AudioInfo.h"
#include "QNetworkReply"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>

namespace {
const QString k_requestUrl = QStringLiteral("https://api.jamendo.com/v3.0/tracks/");
const QString k_clientId   = QStringLiteral("8ccb6b5a");
}

AudioSearchModel::AudioSearchModel(QObject *parent)
    : QAbstractListModel{parent}    
    , m_isSearching(false)
{}

AudioSearchModel *AudioSearchModel::create(QQmlEngine *engine, QJSEngine *jsEngine)
{
    Q_UNUSED(jsEngine)
    Q_UNUSED(engine)
    static AudioSearchModel instance;
    return &instance;
}

int AudioSearchModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_audioList.size();
}

QVariant AudioSearchModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < m_audioList.size()) {
        AudioInfo * audioInfo = m_audioList[index.row()];

        switch((Role) role) {
        case AudioNameRole:
            return audioInfo->title();
        case AudioAuthorRole:
            return audioInfo->authorName();
        case AudioImageSourceRole:
            return audioInfo->imageSource();
        case AudioSourceRole:
            return audioInfo->audioSource();
        default:
            return {};
        }
    }

    return {};
}

QHash<int, QByteArray> AudioSearchModel::roleNames() const
{
    QHash<int, QByteArray> result;

    result[AudioNameRole] = "audioName";
    result[AudioAuthorRole] = "audioAuthor";
    result[AudioImageSourceRole] = "audioImageSource";
    result[AudioSourceRole] = "audioSource";

    return result;
}

void AudioSearchModel::searchSong(const QString &name)
{
    // qDebug() << "searchSong called with: " << name;

    if (!name.trimmed().isEmpty()) {
        if (m_reply) {
            m_reply->abort();
            m_reply->deleteLater();
            m_reply = nullptr;
        }

        QUrlQuery query;
        query.addQueryItem("client_id", k_clientId);
        query.addQueryItem("namesearch", name);
        query.addQueryItem("format", "json");

        setIsSearching(true);

        m_reply = m_networkmanager.get(QNetworkRequest(k_requestUrl + "?" + query.toString()));

        connect(m_reply, &QNetworkReply::finished, this, &AudioSearchModel::parseData);
    }
}

void AudioSearchModel::parseData()
{
    if (!m_reply) {
        setIsSearching(false);
        return;
    }

    if (m_reply->error() == QNetworkReply::NoError) {
        const QByteArray data = m_reply->readAll();

        const QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isObject()) {
            qWarning() << "Jamendo: JSON root is not an object";
        } else {
            const QJsonObject root = doc.object();
            const QJsonObject headers = root.value("headers").toObject();

            // Debug (na chwilę):
            // qDebug() << "status:" << headers.value("status").toString();
            // qDebug() << "raw:" << data;

            beginResetModel();
            qDeleteAll(m_audioList);
            m_audioList.clear();

            if (headers.value("status").toString() == "success") {
                const QJsonArray results = root.value("results").toArray();

                for (const QJsonValue &v : results) {
                    const QJsonObject entry = v.toObject();

                    if (entry.value("audiodownload_allowed").toBool()) {
                        auto *audioInfo = new AudioInfo(this);
                        audioInfo->setTitle(entry.value("name").toString());
                        audioInfo->setAuthorName(entry.value("artist_name").toString());
                        audioInfo->setImageSource(entry.value("image").toString());
                        audioInfo->setAudioSource(entry.value("audiodownload").toString());
                        m_audioList << audioInfo;
                    }
                }
            } else {
                qWarning() << "Jamendo error:" << headers.value("error_message").toString();
            }

            endResetModel();
        }
    } else if (m_reply->error() != QNetworkReply::OperationCanceledError) {
        qCritical() << "Reply failed, error:" << m_reply->errorString();
    }

    setIsSearching(false);
    m_reply->deleteLater();
    m_reply = nullptr;
}

// void AudioSearchModel::parseData()
// {
//     if (m_reply->error() == QNetworkReply::NoError) {
//         beginResetModel();
//         qDeleteAll(m_audioList);
//         m_audioList.clear();

//         QByteArray data = m_reply->readAll();

//         QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
//         QJsonObject headers = jsonDocument["headers"].toObject();

//         if (headers["status"].toString() == "success") {
//             QJsonArray results = jsonDocument["results"].toArray();

//             for (const auto &result : results) {
//                 QJsonObject entry = result.toObject();

//                 if (entry["audiodownload_allowed"].toBool()) {
//                     AudioInfo *audioInfo = new AudioInfo(this);

//                     audioInfo->setTitle(entry["name"].toString());
//                     audioInfo->setAuthorName(entry["artist_name"].toString());
//                     audioInfo->setImageSource(entry["image"].toString());
//                     audioInfo->setAudioSource(entry["audiodownload"].toString());

//                     m_audioList << audioInfo;
//                 }
//             }
//         } else {
//             qWarning() << headers["error_message"];
//         }

//         endResetModel();
//     } else if (m_reply->error() != QNetworkReply::OperationCanceledError) {
//         qCritical() << "Reply failed, error:" << m_reply->errorString();
//     }

//     setIsSearching(false);
//     m_reply->deleteLater();
//     m_reply = nullptr;
// }

bool AudioSearchModel::isSearching() const
{
    return m_isSearching;
}

void AudioSearchModel::setIsSearching(bool newIsSearching)
{
    if (m_isSearching == newIsSearching)
        return;
    m_isSearching = newIsSearching;
    emit isSearchingChanged();
}
