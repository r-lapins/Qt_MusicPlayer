import QtQuick

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

            TextButton {
                id: previousButton

                width: 50
                height: 50

                text: "<"

                onClicked: playerController.switchToPreviousSong()
            }

            TextButton {
                id: playPauseButton

                width: 75
                height: 50

                text: playerController.playing ? "Pause" : "Play"

                onClicked: playerController.playPause()
            }

            TextButton {
                id: nextButton

                width: 50
                height: 50

                text: ">"

                onClicked: playerController.switchToNextSong()
            }
        }
    }

    QtObject {
        id: playerController

        property int currentSongIndex: 0
        property int songCount: 3
        property bool playing: false

        function playPause() {
            playing = !playing
        }

        function switchToPreviousSong() {
            if (currentSongIndex > 0) {
                currentSongIndex--
            } else {
                currentSongIndex = songCount -1
            }
        }

        function switchToNextSong() {
            if (currentSongIndex + 1 >= songCount) {
                currentSongIndex = 0
            } else {
                currentSongIndex++
            }
        }
    }
}
