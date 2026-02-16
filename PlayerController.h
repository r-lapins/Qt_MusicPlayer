#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <qqml.h>
#include <QMediaPlayer>
#include <QAbstractListModel>

class AudioInfo;

class PlayerController : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
    Q_PROPERTY(AudioInfo* currentSong READ currentSong WRITE setCurrentSong NOTIFY currentSongChanged FINAL)

public:
    enum Role {
        AudioTitleRole = Qt::UserRole + 1,
        AudioAuthorNameRole,
        AudioSourceRole,
        AudioImageSourceRole,
        AudioVideoSourceRole
    };

    explicit PlayerController(QObject *parent = nullptr);

    static PlayerController *create(QQmlEngine *engine, QJSEngine *jsEngine);

    bool playing() const;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    AudioInfo *currentSong() const;
    void setCurrentSong(AudioInfo *newCurrentSong);

    // public slots:
    Q_INVOKABLE void switchToNextSong();
    Q_INVOKABLE void switchToPreviousSong();
    Q_INVOKABLE void playPause();
    Q_INVOKABLE void changeAudioSource(const QUrl &source);
    Q_INVOKABLE void addAudio(const QString& title,
                              const QString& authorName,
                              const QUrl& audioSource,
                              const QUrl& imageSource,
                              const QUrl& videoSource = QUrl());
    Q_INVOKABLE void removeAudio(int index);
    Q_INVOKABLE void switchToAudioByIndex(int index);

signals:
    void playingChanged();

    void currentSongChanged();

private:
    bool m_playing = false;
    QMediaPlayer m_mediaPlayer;

    QList<AudioInfo *> m_audioList;                 // PLAYLISTA

    AudioInfo *m_currentSong = nullptr;
};

#endif // PLAYERCONTROLLER_H
