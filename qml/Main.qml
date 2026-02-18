import QtQuick
import QtQuick.Controls
import QtQuick.Window

import com.company.PlayerController
import com.company.AudioSearchModel

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

    SearchFieldX {
      id: searchFieldX

      anchors {
        left: parent.left
        right: closeSearchButton.left
        verticalCenter: parent.verticalCenter
        margins: 20
      }

      height: 30

      visible: !searchPanel.hidden
      enabled: !AudioSearchModel.isSearching

      onAccepted: value => {
                    // console.log("ACCEPTED:", value)
                    AudioSearchModel.searchSong(value)
                    topbar.forceActiveFocus()
                  }
    }

    ImageButton {
      id: playlistIcon

      anchors {
        right: parent.right
        verticalCenter: parent.verticalCenter
        rightMargin: 20
      }

      width: 32
      height: 32
      source: "qrc:/AudioPlayer/assets/icons/menu_icon.png"

      visible: searchPanel.hidden
      onClicked: {
        playlistPanel.hidden = !playlistPanel.hidden
      }
    }

    ImageButton {
      id: closeSearchButton

      anchors {
        right: parent.right
        verticalCenter: parent.verticalCenter
        rightMargin: 20
      }

      width: 32
      height: 32

      source: "qrc:/AudioPlayer/assets/icons/close_icon.png"
      visible: !searchPanel.hidden

      onClicked: {
        searchPanel.hidden = true
      }
    }
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
      enabled: !!PlayerController.currentSong
      opacity: enabled ? 1 : 0.3

      ImageButton {
        id: previousButton

        anchors.verticalCenter: parent.verticalCenter
        width: 64
        height: 64

        source: "qrc:/AudioPlayer/assets/icons/previous.png"

        onClicked: PlayerController.switchToPreviousSong()
      }

      ImageButton {
        id: playPauseButton

        anchors.verticalCenter: parent.verticalCenter
        width: 64
        height: 64

        source: PlayerController.playing ? "qrc:/AudioPlayer/assets/icons/pause.png" : "qrc:/AudioPlayer/assets/icons/play.png"
        onClicked: PlayerController.playPause()
      }

      ImageButton {
        id: nextButton

        anchors.verticalCenter: parent.verticalCenter
        width: 64
        height: 64

        source: "qrc:/AudioPlayer/assets/icons/next.png"

        onClicked: PlayerController.switchToNextSong()
      }
    }
  }

  PlaylistPanel {
    id: playlistPanel

    anchors {
      top: topbar.bottom
    }

    x: hidden ? parent.width : parent.width - width

    onSearchRequested: {
      searchPanel.hidden = false
    }
  }

  SearchPanel {
    id: searchPanel

    anchors {
      left: parent.left
      right: parent.right
    }

    height: mainSection.height + bottombar.height

    y: hidden ? parent.height : topbar.height
  }
}
