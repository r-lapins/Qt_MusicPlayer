#include "PlayerController.h"
#include "AudioInfo.h"

#include <QMediaDevices>
#include <QAudioDevice>
#include <QAudioOutput>

PlayerController::PlayerController(QObject *parent)
    : QObject{parent}
{
    initPlaylist();
    const auto &audioOutputs = QMediaDevices::audioOutputs();
    if (!audioOutputs.isEmpty()) {
        m_mediaPlayer.setAudioOutput(new QAudioOutput(&m_mediaPlayer));     // &m_mediaPlayer - parent
    }
}

PlayerController *PlayerController::create(QQmlEngine *engine, QJSEngine *jsEngine)
{
    Q_UNUSED(jsEngine)
    Q_UNUSED(engine)
    static PlayerController instance;
    return &instance;
}

const QList<AudioInfo *> &PlayerController::songs() const
{
    return m_songs;
}

int PlayerController::currentSongIndex() const
{
    return m_currentSongIndex;
}

bool PlayerController::playing() const
{
    return m_playing;
}

void PlayerController::switchToNextSong()
{
    if (m_songs.isEmpty())
        return;

    if (m_currentSongIndex + 1 >= m_songs.size()) {
        m_currentSongIndex = 0;
    } else {
        m_currentSongIndex++;
    }

    emit currentSongIndexChanged();
    emit currentSongChanged();

    auto *info = m_songs.at(m_currentSongIndex);
    if (info) {
        changeAudioSource(info->audioSource());
    }
}

void PlayerController::switchToPreviousSong()
{
    if (m_songs.isEmpty())
        return;

    if (m_currentSongIndex -1 < 0) {
        m_currentSongIndex = m_songs.size() -1;
    } else {
        m_currentSongIndex--;
    }

    emit currentSongIndexChanged();
    emit currentSongChanged();

    auto *info = m_songs.at(m_currentSongIndex);
    if (info) {
        changeAudioSource(info->audioSource());
    }
}

void PlayerController::playPause()
{
    m_playing = !m_playing;
    emit playingChanged();

    if (m_playing) {
        m_mediaPlayer.play();
    } else {
        m_mediaPlayer.pause();
    }
}

void PlayerController::changeAudioSource(const QUrl &source)
{
    m_mediaPlayer.setSource(source);   // tylko audio

    if (m_playing) {
        m_mediaPlayer.play();
    }
}

AudioInfo *PlayerController::currentSong() const
{
    if (m_currentSongIndex < 0 || m_currentSongIndex >= m_songs.size())
        return nullptr;
    return m_songs[m_currentSongIndex];
}

void PlayerController::initPlaylist()
{
    // utwór 1
    {
        auto *info = new AudioInfo(this);
        info->setSongIndex(0);
        info->setTitle("Eine kleine maine Dame");
        info->setAuthorName("Rammstungerenzig");
        info->setImageSource(QUrl("qrc:/AudioPlayer/assets/images/image1.jpg"));
        info->setAudioSource(QUrl("qrc:/AudioPlayer/assets/audio/eine_kleine_nachtmusik.wav"));
        m_songs.append(info);
    }

    // utwór 2
    {
        auto *info = new AudioInfo(this);
        info->setSongIndex(1);
        info->setTitle("Meine Mutter");
        info->setAuthorName("Radio dla Polaków");
        info->setImageSource(QUrl("qrc:/AudioPlayer/assets/images/image2.jpg"));
        info->setAudioSource(QUrl("qrc:/AudioPlayer/assets/audio/air_on_the_g_string.wav"));
        m_songs.append(info);
    }

    // utwór 3
    {
        auto *info = new AudioInfo(this);
        info->setSongIndex(2);
        info->setTitle("Poranne zorze");
        info->setAuthorName("Franek Jodełka");
        info->setImageSource(QUrl("qrc:/AudioPlayer/assets/images/image3.jpg"));
        info->setAudioSource(QUrl("qrc:/AudioPlayer/assets/audio/symphony_no_5.wav"));
        info->setVideoSource(QUrl("qrc:/AudioPlayer/assets/videos/video_1.mp4"));
        m_songs.append(info);
    }

    // qDebug() << "HAAAAAAAAAAAAAAAAAAAAAAAAAAALOOO!!!!!!" << m_songs[2]->authorName();
    emit songsChanged();
}
