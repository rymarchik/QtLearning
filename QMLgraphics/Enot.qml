import QtQuick 2.7
import QtQuick.Window 2.2

Window {
    visible: true
    color: "orange"
    width: img.width
    height: img.height

    Image {
        id: img
        source: "qrc:///enot.jpg"
        transform: [
            Scale {
                origin.x: width / 2
                origin.y: height / 2
                xScale: 0.5
                yScale: 0.5
            },
            Rotation {
                origin.x: width / 2
                origin.y: height /2
                angle: -30
            }
        ]
    }
}
