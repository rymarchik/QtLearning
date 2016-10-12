import QtQuick 2.7
import QtQuick.Window 2.2
import QtPositioning 5.5
import QtLocation 5.6
import QtQuick.Controls 1.4
import "helper.js" as Helper

//Rectangle {
//    width: 800
//    height: 480



    Map {
        width: 800
        height: 480
//        anchors.fill: parent
        id: map
        plugin: here
        property variant locationVolat: QtPositioning.coordinate(53.931052, 27.634170)
        property variant scaleLengths: [5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000]

        function calculateScale()
        {
            var coord1, coord2, dist, text, f
            f = 0
            coord1 = map.toCoordinate(Qt.point(0,scale.y))
            coord2 = map.toCoordinate(Qt.point(0+scaleImage.sourceSize.width,scale.y))
            dist = Math.round(coord1.distanceTo(coord2))

            if (dist === 0) {
                // not visible
            } else {
                for (var i = 0; i < scaleLengths.length-1; i++) {
                    if (dist < (scaleLengths[i] + scaleLengths[i+1]) / 2 ) {
                        f = scaleLengths[i] / dist
                        dist = scaleLengths[i]
                        break;
                    }
                }
                if (f === 0) {
                    f = dist / scaleLengths[i]
                    dist = scaleLengths[i]
                }
            }

            text = Helper.formatDistance(dist)
            scaleImage.width = (scaleImage.sourceSize.width * f) - 2 * scaleImageLeft.sourceSize.width
            scaleText.text = text
        }


        gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.FlickGesture | MapGestureArea.PinchGesture
        gesture.flickDeceleration: 3000
        gesture.enabled: true

        onCenterChanged:{
            scaleTimer.restart()
        }

        onZoomLevelChanged:{
            scaleTimer.restart()
            zoomSlider.value = map.zoomLevel
        }

        onWidthChanged:{
            scaleTimer.restart()
        }

        onHeightChanged:{
            scaleTimer.restart()
        }
//        activeMapType: MapType.TerrainMap
//        activeMapType: map.supportedMapTypes[6]

        center {
//            latitude: myLatitude
//            longitude: myLongitude
            latitude: 53.931052
            longitude: 27.634170
        }
        zoomLevel: 16

        MapQuickItem {
            id: marker
//            coordinate: QtPositioning.coordinate(myLatitude, myLongitude)
            coordinate: QtPositioning.coordinate(53.931052, 27.634170)
            sourceItem: Image {
                id: image; source: "marker.png"
            }
            anchorPoint: Qt.point(image.width/2, image.height)
        }

        Slider {
            id: zoomSlider;
            z: map.z + 3
            minimumValue: map.minimumZoomLevel;
            maximumValue: map.maximumZoomLevel;
            anchors.margins: 10
            anchors.bottom: scale.top
            anchors.top: parent.top
            anchors.right: parent.right
            orientation : Qt.Vertical
            value: map.zoomLevel
            onValueChanged: {
                map.zoomLevel = value
            }
        }

        Item {
            id: scale
            z: map.z + 3
            visible: scaleText.text != "0 m"
            anchors.bottom: parent.bottom;
            anchors.right: parent.right
            anchors.margins: 20
            height: scaleText.height * 2
            width: scaleImage.width

            Image {
                id: scaleImageLeft
                source: "resources/scale_end.png"
                anchors.bottom: parent.bottom
                anchors.right: scaleImage.left
            }
            Image {
                id: scaleImage
                source: "resources/scale.png"
                anchors.bottom: parent.bottom
                anchors.right: scaleImageRight.left
            }
            Image {
                id: scaleImageRight
                source: "resources/scale_end.png"
                anchors.bottom: parent.bottom
                anchors.right: parent.right
            }
            Label {
                id: scaleText
                color: "#004EAE"
                anchors.centerIn: parent
                text: "0 m"
            }
            Component.onCompleted: {
                map.calculateScale();
            }
        }

        Timer {
            id: scaleTimer
            interval: 100
            running: false
            repeat: false
            onTriggered: {
                map.calculateScale()
            }
        }

        Plugin {
            id: osm
            name: "osm"
            PluginParameter {
                name: "osm.mapping.host";
                value: "http://a.tile.openstreetmap.org/"
            }
        }
        Plugin {
            id: here
            name: "here"
            PluginParameter { name: "here.app_id"; value: "bPTNwzHlkiS3xScHR1yO" }
            PluginParameter { name: "here.token"; value: "BX9WhKp3gZiNa2J4chisQQ" }
        }
        Plugin {
            id: mapbox
            name: "mapbox"
            PluginParameter { name: "mapbox.map_id"; value: "mapbox.satellite" }
            PluginParameter { name: "mapbox.access_token"; value: "pk.eyJ1IjoiaW5zdXJnIiwiYSI6ImNpdHh6Mno5eDAwM3Yybms5bmE1c2xuNHoifQ.vtH2RrfMDazayR93b3qidw" }
        }
    }

//    Plugin {
//        id: osm
//        name: "osm"
//        PluginParameter { name: "osm.useragent"; value: "My great Qt OSM application" }
//        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
//        PluginParameter { name: "osm.mapping.copyright"; value: "All mine" }
//        PluginParameter { name: "osm.routing.host"; value: "http://osrm.server.address/viaroute" }
//        PluginParameter { name: "osm.geocoding.host"; value: "http://geocoding.server.address" }
//    }


//    PositionSource {
//        id: pos
//        nmeaSource: "nmeadata.txt"
//        updateInterval: 5000
//        active: true
//        onPositionChanged: {
//            // center the map on the current position
//            map.center = position.coordinate
//            var coord = pos.position.coordinate;
//            console.log("Coordinate:", coord.longitude, coord.latitude);
//        }
//    }
//}
