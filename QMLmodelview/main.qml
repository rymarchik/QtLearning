import QtQuick 2.7
import QtQuick.Window 2.2

Window {
    id: mainwindow
    visible: true
    width: 200
    height: 360
    Component {
        id: delegate
        Item {
            width: mainwindow.width
            height: 70
            Row {
                anchors.verticalCenter: parent.verticalCenter
                Image {
                    width: 64
                    height: 64
                    source: image
                }
                Column {
                    Text {color: "white"; text: game; font.pointSize: 12}
                    Text {color: "lightblue"; text: producer; font.pointSize: 10}
                    Text {color: "yellow"; text: year; font.pointSize: 8}
                }
            }
        }
    }
    ListView {
        anchors.fill: parent
        focus: true
        header: Rectangle {
            width: parent.width
            height: 30
            gradient: Gradient {
                GradientStop {position: 0; color: "gray"}
                GradientStop {position: 0.7; color: "black"}
            }
            Text {
                anchors.centerIn: parent
                color: "gray"
                text: "Top games by A.Rymarchik"
                font.bold: true
                font.pointSize: 20
            }
        }
        footer: Rectangle {
            width: parent.width
            height: 30
            gradient: Gradient {
                GradientStop {position: 0; color: "gray"}
                GradientStop {position: 0.7; color: "black"}
            }
        }
        highlight: Rectangle {
            width: parent.width
            color: "blue"
        }
        model: games()
        delegate: delegate
    }

//    Flickable {
//        anchors.fill: parent
//        contentWidth: img.width
//        contentHeight: img.height
//        Image {
//            id: img
//            source: "qrc:///yoba_full.png"
//        }
//    }
}
