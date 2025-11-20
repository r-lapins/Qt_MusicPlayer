#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <QMediaPlayer>

class AudioInfo;

class PlayerController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentSongIndex READ currentSongIndex NOTIFY currentSongIndexChanged)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
    Q_PROPERTY(QList<AudioInfo*> songs READ songs NOTIFY songsChanged)
    Q_PROPERTY(AudioInfo* currentSong READ currentSong NOTIFY currentSongChanged)

public:
    explicit PlayerController(QObject *parent = nullptr);

    static PlayerController *create(QQmlEngine *engine, QJSEngine *jsEngine);

    const QList<AudioInfo*>& songs() const;     // PLAYLISTA

    int currentSongIndex() const;
    bool playing() const;

    Q_INVOKABLE void switchToNextSong();
    Q_INVOKABLE void switchToPreviousSong();
    Q_INVOKABLE void playPause();
    Q_INVOKABLE void changeAudioSource(const QUrl &source);

    AudioInfo *currentSong() const;

signals:
    void songsChanged();
    void currentSongIndexChanged();
    void playingChanged();
    void currentSongChanged();

private:
    QList<AudioInfo *> m_songs;                 // PLAYLISTA
    void initPlaylist();
    int m_currentSongIndex = 0;
    bool m_playing = false;
    QMediaPlayer m_mediaPlayer;
    AudioInfo *m_currentSong = nullptr;
};

#endif // PLAYERCONTROLLER_H
