import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

//import QtQuick.Window 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Quit"
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle {
        id: rect1
        color: "darkkhaki"
        width: parent.width / 1.5
        height: parent.height / 1.5
        anchors.top: parent.top
        anchors.left: parent.left
        border.color: "black"

        opacity: focus ? 1 : 0.3
        KeyNavigation.tab: rect2
        KeyNavigation.backtab: movingText
        focus: true

        onWidthChanged: {
            console.log("width changed:" + width)
        }
        onHeightChanged: {
            console.log("height changed:" + height)
        }
    }

    Rectangle {
        id: rect2
        color: "aqua"
        anchors.top: rect1.verticalCenter
        anchors.bottom: parent.bottom
        anchors.left: rect1.horizontalCenter
        anchors.right: parent.right
        border.color: "red"

        opacity: focus ? 1 : 0.3
        KeyNavigation.tab: rect1
        KeyNavigation.backtab: movingText
    }

    Item {
        id: elem
        property string name: "My element"
        property int ver: 1
        property real pi: 3.1415
        property bool condition: true
        property url link: "tut.by"
    }

    Text {
        id: movingText
        x: rect1.width
        y: 0
        text: elem.name + "<br>" + elem.ver + "<br>" + elem.pi + "<br>" + elem.condition + "<br>" + elem.link
        font.family: "Lucida Calligraphy"
        font.bold: true
        font.pointSize: 12

        Keys.onLeftPressed: x -= 3
        Keys.onRightPressed: x += 3
        Keys.onUpPressed: y -= 3
        Keys.onDownPressed: y += 3
    }

    MyElement {
        id: my
        x: 0
        y: rect1.height
        color: "yellow"
        text: "TEXT TEXT TEXT<br>TEXT TEXT TEXT<br>" + name
        border.width: 1
    }

    Button {
        id: button
        text: "Choose color"
        anchors.centerIn: parent
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.verticalCenter: parent.verticalCenter
        onClicked: {
            message.visible = false;
            color.visible = true;
        }
    }

    ColorDialog {
        id: color
        visible: false
        modality: Qt.WindowModal
        title: "Select a color"
        color: "blue"
        onAccepted: {
            message.informativeText = "Selected color: " + color
            message.visible = true
        }
    }

    MessageDialog {
        id: message
        visible: false
        modality: Qt.NonModal
        title: "Message"
    }

    Calendar {
        width: rect1.width / 2
        height: rect1.height / 2
    }

    ProgressBar {
        id: bar
        y: (4/5)*parent.height
        width: parent.width
        height: (1/5)*parent.height / 2
        value: slider.value
    }

    Slider {
        id: slider
        y: (4/5)*parent.height + bar.height
        width: parent.width
        height: (1/5)*parent.height / 2
        value: 0.75
//        stepSize: 0.1
    }
}
