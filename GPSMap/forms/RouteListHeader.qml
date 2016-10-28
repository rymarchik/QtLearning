import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    property alias travelTime: travelTimeLabel
    property alias distance: distanceLabel
    width: parent.width
    height: tabTitle.height * 4

    Rectangle {
        id: tabRectangle
        height: tabTitle.height * 3
        color: "#46a2da"
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            id: tabTitle
            color: "#ffffff"
            text: qsTr("Route Information")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
            id: travelTimeLabel
            text: totalTravelTime
            color: "#ffffff"
            font.bold: true
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
        }

        Label {
            id: distanceLabel
            text: totalDistance
            color: "#ffffff"
            font.bold: true
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
