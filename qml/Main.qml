import QtQuick
import com.company.PlayerController

Window {
  id: root

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
      id: audioInfoBox

      anchors {
        verticalCenter: parent.verticalCenter
        left: parent.left
        right: parent.right
        margins: 20
      }

      infoProvider: PlayerController.currentSong
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

        source: "qrc:/AudioPlayer/assets/icons/previous.png"

        onClicked: PlayerController.switchToPreviousSong()
      }

      ImageButton {
        id: playPauseButton

        width: 64
        height: 64

        source: PlayerController.playing ? "qrc:/AudioPlayer/assets/icons/pause.png" : "qrc:/AudioPlayer/assets/icons/play.png"

        onClicked: PlayerController.playPause()
      }

      ImageButton {
        id: nextButton

        width: 64
        height: 64

        source: "qrc:/AudioPlayer/assets/icons/next.png"

        onClicked: PlayerController.switchToNextSong()
      }
    }
  }
}
