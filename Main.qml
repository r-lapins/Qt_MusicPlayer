import QtQuick
import com.company.PlayerController

Window {
  width: 640
  height: 640
  visible: true
  title: qsTr("Song Player")

  Rectangle {
    id: topbar

    anchors {
      top: parent.top
      left: parent.left
      right: parent.right
    }

    height: 50
    color: "#5f8575"
  }

  Rectangle {
    id: mainSection

    anchors {
      top: topbar.bottom
      bottom: bottombar.top
      left: parent.left
      right: parent.right
    }

    color: "#1e1e1e"

    AudioInfoBox {
      id: firstSong

      anchors {
        verticalCenter: parent.verticalCenter
        left: parent.left
        right: parent.right
        margins: 20
      }

      songIndex: 0
      title: "Eine kleine Nachtmusik"
      authorName: "Rammstein"
      imageSource: "qrc:/assets/images/image1.jpg"
    }

    AudioInfoBox {
      id: secondSong

      anchors {
        verticalCenter: parent.verticalCenter
        left: parent.left
        right: parent.right
        margins: 20
      }

      songIndex: 1
      title: "Meine Mutter"
      authorName: "Radio dla Polaków"
      imageSource: "qrc:/assets/images/image2.jpg"
    }

    AudioInfoBox {
      id: thirdSong

      anchors {
        verticalCenter: parent.verticalCenter
        left: parent.left
        right: parent.right
        margins: 20
      }

      songIndex: 2
      title: "Poranne zorze"
      authorName: "Franek Jodełka"
      imageSource: "qrc:/assets/images/image3.jpg"
      videoSource: "qrc:/assets/videos/video_1.mp4"
    }
  }

  Rectangle {
    id: bottombar

    anchors {
      bottom: parent.bottom
      left: parent.left
      right: parent.right
    }

    height: 100
    color: "#333333"

    Row {
      anchors.centerIn: parent

      spacing: 20

      ImageButton {
        id: previousButton

        width: 64
        height: 64

        source: "qrc:/assets/icons/previous.png"

        onClicked: PlayerController.switchToPreviousSong()
      }

      ImageButton {
        id: playPauseButton

        width: 64
        height: 64

        source: PlayerController.playing ? "qrc:/assets/icons/pause.png" : "qrc:/assets/icons/play.png"

        onClicked: PlayerController.playPause()
      }

      ImageButton {
        id: nextButton

        width: 64
        height: 64

        source: "qrc:/assets/icons/next.png"

        onClicked: PlayerController.switchToNextSong()
      }
    }
  }
}
