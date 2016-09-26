import QtQuick 2.7
import QtQuick.Window 2.2

Window {
    visible: true
    width: 500
    height: 500
    title: qsTr("Rotating racoon")


    ColorAnimation on color {
        from: Qt.rgba(1, 0.5, 0)
        to: Qt.rgba(0.5, 0, 1)
        duration: 4000
        running: true
        loops: Animation.Infinite
    }

    Rectangle {
        color: "blue"
        NumberAnimation on width {
            from: width
            to: 0
            duration: 2000
            running: true
            loops: Animation.Infinite
            easing.type: Easing.InOutExpo
        }
        NumberAnimation on height {
            from: height
            to: 0
            duration: 2000
            running: true
            loops: Animation.Infinite
            easing.type: Easing.InOutExpo
        }
    }

    Image {
        id: yoba
        source: "qrc:///yoba.png"
        onXChanged: {
            if (x == parent.width - width && y == parent.height - height) {
                rot.pause();
                msg.opacity = 1;
            }
            else {
                rot.resume();
                msg.opacity = 0;
            }
        }

        RotationAnimation on rotation {
            id: rot
            from: 0
            to: 360
            duration: 3000
            loops: Animation.Infinite
            easing.type: Easing.InOutCirc
        }
    }

    Image {
        id: msg
        source: "qrc:///message.png"
        x: parent.width - width
        y: parent.height - height - yoba.height
        opacity: 0

        Text {
            anchors.centerIn: parent
            text: "yo!"
            font.family: "Jokerman"
            font.bold: true
            font.pointSize: 12
        }
    }

    SequentialAnimation {
        NumberAnimation {
            target: yoba
            from: 0
            to: width - yoba.width
            properties: "x"
            duration: 3000
            easing.type: Easing.InOutSine
        }
        ParallelAnimation {
            NumberAnimation {
                target: yoba
                properties: "x"
                from: width - yoba.width
                to: 0
                duration: 3000
                easing.type: Easing.InOutSine
            }
            NumberAnimation {
                target: yoba
                properties: "y"
                from: 0
                to: height - yoba.height
                duration: 3000
                easing.type: Easing.InOutSine
            }
        }
        NumberAnimation {
            target: yoba
            properties: "x"
            from: 0
            to: width - yoba.width
            duration: 3000
            easing.type: Easing.InOutSine
        }
        PauseAnimation {
            duration: 2000
        }
        ParallelAnimation {
            NumberAnimation {
                target: yoba
                properties: "x"
                from: width - yoba.width
                to: 0
                duration: 3000
                easing.type: Easing.InOutSine
            }
            NumberAnimation {
                target: yoba
                properties: "y"
                from: height - yoba.height
                to: 0
                duration: 3000
                easing.type: Easing.InOutSine
            }
        }
        running: true
        loops: Animation.Infinite
    }

    Image {
        id: rac
        source: "qrc:///enot.jpg"

        Behavior on x {
            NumberAnimation {
                easing.type: Easing.OutSine
                duration: 1000
            }
        }
        Behavior on y {
            NumberAnimation {
                easing.type: Easing.OutSine
                duration: 1000
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onMouseXChanged: rac.x = mouseX
        onMouseYChanged: rac.y = mouseY
    }

//    PropertyAnimation {
//        target: rac
//        properties: "x, y"
//        from: 0
//        to: height - rac.height
//        duration: 3500
//        running: true
//        loops: Animation.Infinite
//        easing.type: Easing.InOutBounce
//    }
}
