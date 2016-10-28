import QtQuick 2.3
import QtQuick.Controls 1.2
import ArcGIS.Runtime 10.26

ApplicationWindow {
    id: appWindow
    width: 800
    height: 600
    title: "MyMap"

    Map {
        anchors.fill: parent

        focus: true

        ArcGISTiledMapServiceLayer {
            url: "http://server.arcgisonline.com/ArcGIS/rest/services/World_Street_Map/MapServer"
        }
    }
}
