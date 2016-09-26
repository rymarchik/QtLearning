import QtQuick 2.7
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QooQoo")

    Rectangle {
        id: rect
        anchors.verticalCenter: parent.verticalCenter
        state: "state 1"
        Text {
            id: text
            anchors.centerIn: parent
        }
        states: [
            State {
                name: "state 1"
                PropertyChanges {
                    target: rect
                    color: "red"
                    x: 0
                    width: 200
                    height: 200
                    border.width: 3
                    border.color: "green"
                }
                PropertyChanges {
                    target: text
                    text: "QooQoo! It's state 1!"
                }
            },
            State {
                name: "state 2"
                PropertyChanges {
                    target: rect
                    color: "yellow"
                    x: parent.width - width
                    width: 150
                    height: 150
                    border.width: 2
                    border.color: "blue"
                }
                PropertyChanges {
                    target: text
                    text: "QooQoo! It's state 2!"
                }
            }
        ]
        transitions: [
            Transition {
                from: "state 1"
                to: "state 2"
                PropertyAnimation {
                    target: rect;
                    properties: "x, color, width, height, border.width, border.color"
                    duration: 2000
                    easing.type: Easing.OutBack
                }
            },
            Transition {
                from: "state 2"
                to: "state 1"
                PropertyAnimation {
                    target: rect;
                    properties: "x, color, width, height, border.width, border.color"
                    duration: 2000
                    easing.type: Easing.OutCirc
                }
            }
        ]
        MouseArea {
            anchors.fill: parent
            onClicked: parent.state = (parent.state == "state 1") ? "state 2": "state 1"
        }
    }
}
