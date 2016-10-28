import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    id: root
    property bool checked: false
    property alias routeInstruction: instructionLabel
    property alias routeDistance: distanceLabel
    property alias routeIndex: indexLabel

    width: parent.width
    height: indexLabel.height * 2

    RowLayout {
        spacing: 10
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.verticalCenter: parent.verticalCenter
        Label {
            id: indexLabel
        }
        Label {
            id: instructionLabel
            wrapMode: Text.Wrap
        }
        Label {
            id: distanceLabel
        }
    }

//    Rectangle {
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.margins: 15
//        height: 1
//        color: "#46a2da"
//    }
}



