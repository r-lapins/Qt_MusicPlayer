import QtQuick
import QtMultimedia
import com.company.PlayerController

Item {
  id: root

  visible: !!PlayerController.currentSong

  Image {
    id: albumImage

    anchors {
      verticalCenter: parent.verticalCenter
      left: parent.left
    }

    width: 150
    height: 150

    source: !!PlayerController.currentSong ? PlayerController.currentSong.imageSource : ""
  }

  MediaPlayer {
    id: mediaPlayer
    source: !!PlayerController.currentSong ? PlayerController.currentSong.videoSource : ""
    videoOutput: videoOutput
    autoPlay: true
    loops: MediaPlayer.Infinite
  }

  VideoOutput {
    id: videoOutput
    width: 150
    height: 150
    anchors {
      verticalCenter: parent.verticalCenter
      right: parent.right
    }
  }

  Text {
    id: titleText

    anchors {
      bottom: parent.verticalCenter
      left: albumImage.right
      margins: 20
      right: parent.right
    }

    color: "white"
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    text: !!PlayerController.currentSong ? PlayerController.currentSong.title : ""

    font {
      pixelSize: 20
      bold: true
    }
  }

  Text {
    id: authorText

    anchors {
      top: parent.verticalCenter
      left: titleText.left
      topMargin: 5
      right: parent.right
    }

    color: "gray"
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    text: !!PlayerController.currentSong ? PlayerController.currentSong.authorName : ""

    font {
      pixelSize: 16
    }
  }

  onVisibleChanged: {
    if (visible) {
      mediaPlayer.play()
    } else {
      mediaPlayer.stop()
      mediaPlayer.position = 0
    }
  }

  // console.log("infoProvider =", infoProvider)
  // console.log("infoProvider.songIndex =",
  //             infoProvider ? infoProvider.songIndex : "NULL")
  // console.log("PlayerController.currentSongIndex =",
  //             PlayerController.currentSongIndex)
}
