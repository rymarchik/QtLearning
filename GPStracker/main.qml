import QtQuick 2.7
import QtQuick.Window 2.2
import QtPositioning 5.5
import QtLocation 5.6

Rectangle {
//    visible: true
    width: 800
    height: 480
//    title: qsTr("My location!")
    property variant locationVolat: QtPositioning.coordinate(53.931052, 27.634170)

//    Plugin {
//        id: osm
//        name: "osm"
//        PluginParameter { name: "osm.useragent"; value: "My great Qt OSM application" }
//        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
//        PluginParameter { name: "osm.mapping.copyright"; value: "All mine" }
//        PluginParameter { name: "osm.routing.host"; value: "http://osrm.server.address/viaroute" }
//        PluginParameter { name: "osm.geocoding.host"; value: "http://geocoding.server.address" }
//    }
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

    Map {
        anchors.fill: parent
        id: map

        plugin: here
//        activeMapType: MapType.TerrainMap
//        activeMapType: map.supportedMapTypes[6]

        center {
            latitude: myLatitude
            longitude: myLongitude
        }
        zoomLevel: 16

        MapQuickItem {
            id: marker
            coordinate: QtPositioning.coordinate(myLatitude, myLongitude)
            anchorPoint.x: image.width/2
            anchorPoint.y: image.height

            sourceItem: Image {
                id: image; source: "marker.png"
            }
            zoomLevel: 16

        }
    }

    PositionSource {
        id: pos
        nmeaSource: "nmeadata.txt"
        updateInterval: 5000
        active: true
        onPositionChanged: {
            // center the map on the current position
            map.center = position.coordinate
            var coord = pos.position.coordinate;
            console.log("Coordinate:", coord.longitude, coord.latitude);
        }
    }
}
