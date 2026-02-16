import QtQuick

Image {
  id: root

  signal clicked

  opacity: buttonMouseArea.containsMouse ? 0.15 : 1
  mipmap: true
  fillMode: Image.PreserveAspectFit

  MouseArea {
    id: buttonMouseArea

    anchors.fill: parent

    hoverEnabled: true

    onClicked: {
      root.clicked()
    }
  }
}
