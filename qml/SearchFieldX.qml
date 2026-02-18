import QtQuick
import QtQuick.Controls

Rectangle {
  property int __crash: doesNotExist

  id: root

  signal accepted(string value)

  color: "#1e1e1e"
  border.color: searchInput.activeFocus ? Qt.lighter("#5F8575") : "transparent"
  border.width: 1

  opacity: enabled ? 1 : 0.6

  TextInput {
    id: searchInput

    anchors.fill: parent
    font.pixelSize: 14
    color: "white"

    leftPadding: 30
    verticalAlignment: TextInput.AlignVCenter

    // Keys.onPressed: e => console.log("key:", e.key)
    Image {
      anchors {
        left: parent.left
        leftMargin: 5
        verticalCenter: parent.verticalCenter
      }

      width: 16
      height: 16

      mipmap: true
      source: "qrc:/AudioPlayer/assets/icons/search_icon.png"
    }

    onAccepted: {
      root.accepted(text)
    }
  }
}
