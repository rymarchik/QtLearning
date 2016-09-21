import QtQuick 2.7

Rectangle {
    property alias text: txt.text
    property string name: "TextField"

    width: txt.width
    height: txt.height

    Text {
        id: txt
        x: 0
        y:0
    }
}
