#ifndef AUDIOSEARCHMODEL_H
#define AUDIOSEARCHMODEL_H

#include <qqml.h>
#include <QAbstractListModel>
#include <QNetworkAccessManager>

class AudioInfo;

class AudioSearchModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool isSearching READ isSearching NOTIFY isSearchingChanged FINAL)

public:
    enum Role {
        AudioNameRole = Qt::UserRole + 1,
        AudioAuthorRole,
        AudioImageSourceRole,
        AudioSourceRole
    };

    explicit AudioSearchModel(QObject *parent = nullptr);

    static AudioSearchModel *create(QQmlEngine *engine, QJSEngine *jsEngine);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    bool isSearching() const;
    void setIsSearching(bool newIsSearching);

    Q_INVOKABLE void searchSong(const QString &name);

public slots:
    void parseData();

signals:
    void isSearchingChanged();

private:
    QList<AudioInfo*> m_audioList;
    QNetworkAccessManager m_networkmanager;
    QNetworkReply *m_reply = nullptr;
    bool m_isSearching;
};

#endif // AUDIOSEARCHMODEL_H
