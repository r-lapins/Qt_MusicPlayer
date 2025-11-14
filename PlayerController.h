#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>

class PlayerController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentSongIndex READ currentSongIndex NOTIFY currentSongIndexChanged FINAL)
    Q_PROPERTY(int songCount READ songCount NOTIFY songCountChanged FINAL)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged FINAL)

public:
    explicit PlayerController(QObject *parent = nullptr);

    int currentSongIndex() const;
    int songCount() const;
    bool playing() const;

    Q_INVOKABLE void switchToNextSong();

public slots:
    void switchToPreviousSong();
    void playPause();

signals:
    void currentSongIndexChanged();
    void songCountChanged();
    void playingChanged();

private:
    int m_currentSongIndex = 0;
    int m_songCount = 3;
    bool m_playing = false;
};

#endif // PLAYERCONTROLLER_H
