import QtQuick 2.7
import QtQuick.Window 2.2
import QtPositioning 5.5
import QtLocation 5.6

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//    Plugin {
//        id: osm
//        name: "osm"
//        PluginParameter { name: "osm.useragent"; value: "My great Qt OSM application" }
//        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
//        PluginParameter { name: "osm.mapping.copyright"; value: "All mine" }
//        PluginParameter { name: "osm.routing.host"; value: "http://osrm.server.address/viaroute" }
//        PluginParameter { name: "osm.geocoding.host"; value: "http://geocoding.server.address" }
//    }
//    Plugin {
//        id: here
//        name: "here"
//        PluginParameter { name: "here.app_id"; value: "bPTNwzHlkiS3xScHR1yO" }
//        PluginParameter { name: "here.token"; value: "BX9WhKp3gZiNa2J4chisQQ" }
//    }
        Plugin {
            id: mapbox
            name: "mapbox"
            PluginParameter { name: "mapbox.map_id"; value: "mapbox.landsat-live" }
            PluginParameter { name: "mapbox.access_token"; value: "pk.eyJ1IjoiaW5zdXJnIiwiYSI6ImNpdHh6Mno5eDAwM3Yybms5bmE1c2xuNHoifQ.vtH2RrfMDazayR93b3qidw" }
        }
//pk.eyJ1IjoiaW5zdXJnIiwiYSI6ImNpdHh6Mno5eDAwM3Yybms5bmE1c2xuNHoifQ.vtH2RrfMDazayR93b3qidw
    Map {
        anchors.fill: parent
        id: map

        plugin: mapbox
//        activeMapType: MapType.TerrainMap

        center {
            latitude: 53.5
            longitude: 27.5
        }
        zoomLevel: map.maximumZoomLevel

        gesture.enabled: true
    }

    PositionSource {
        onPositionChanged: {
            // center the map on the current position
            map.center = position.coordinate
        }
    }
}
