import QtQuick 2.2
import QtQuick.Window 2.2

Window {
    visible: true
    width: 400
    height: 400
    color: "lightgreen"
    signal mousePositionChanged(real x, real y);
    onMousePositionChanged: color = Qt.rgba(x / width, y / height, 1);

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton | Qt.LeftButton
        onPressed: {
            if (mouse.button === Qt.RightButton)
                color = "yellow"
            else
                color = "aqua"
        }
        onReleased: {
            color = "lightgreen"
        }
        hoverEnabled: true
        onEntered: color = "red"
        onExited: color = "lightgreen"
        onMouseXChanged: mousePositionChanged(mouseX, mouseY)
        onMouseYChanged: mousePositionChanged(mouseX, mouseY)
    }

    Canvas {
        anchors.fill: parent
        onPaint: {
            function drawFantasy() {
                ctx.beginPath()
                ctx.translate(parent.width / 2, parent.height / 2)
                var fAngle = 91 * 3.1415 / 180
                for (var i = 0; i < 1000; ++i) {
                    var n = i * 2
                    ctx.moveTo(0, 0)
                    ctx.lineTo(n , 0)
                    ctx.translate(n, 0)
                    ctx.rotate(fAngle)
                }
                ctx.closePath()
            }
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, parent.width, parent.height)
            ctx.save();
            ctx.strokeStyle = "black"
            ctx.lineWidth = 1

            drawFantasy();

            ctx.stroke();
            ctx.restore();
        }
    }
}
