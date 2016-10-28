import QtQuick 2.7
import QtQuick.Window 2.2
import QtPositioning 5.5
import QtLocation 5.6
import QtQuick.Controls 1.4
import "helper.js" as Helper

Map {
    width: 800
    height: 480
//        anchors.fill: parent
    id: map
    plugin: here
    property variant locationVolat: QtPositioning.coordinate(53.931052, 27.634170)
    property variant scaleLengths: [5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000]
    property variant markers
    property int markerCounter: 0
    property int currentMarker
    property int lastX : -1
    property int lastY : -1
    property int pressX : -1
    property int pressY : -1
    property int jitterThreshold : 30
    property alias routeQuery: routeQuery
    property alias routeModel: routeModel

    signal showMainMenu(variant coordinate)
    signal showMarkerMenu(variant coordinate)
    signal showRouteList()
    signal coordinatesCaptured(double latitude, double longitude)

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

    function addMarker()
    {
        var count = map.markers.length
        markerCounter++
        var marker = Qt.createQmlObject ('Marker {}', map)
        map.addMapItem(marker)
        marker.z = map.z+1
        marker.coordinate = mouseArea.lastCoordinate

        //update list of markers
        var myArray = new Array()
        for (var i = 0; i<count; i++){
            myArray.push(markers[i])
        }
        myArray.push(marker)
        markers = myArray
    }

    function deleteMarker(index)
    {
        //update list of markers
        var myArray = new Array()
        var count = map.markers.length
        for (var i = 0; i<count; i++){
            if (index != i) myArray.push(map.markers[i])
        }

        map.removeMapItem(map.markers[index])
        map.markers[index].destroy()
        map.markers = myArray
        if (markers.length == 0) markerCounter = 0
    }

    function deleteMarkers()
    {
        var count = map.markers.length
        for (var i = 0; i<count; i++){
            map.removeMapItem(map.markers[i])
            map.markers[i].destroy()
        }
        map.markers = []
        markerCounter = 0
    }

    function calculateMarkerRoute()
    {
        routeQuery.clearWaypoints();
        for (var i = currentMarker; i< map.markers.length; i++){
            routeQuery.addWaypoint(markers[i].coordinate)
        }
        routeQuery.travelModes = RouteQuery.CarTravel
        routeQuery.routeOptimizations = RouteQuery.ShortestRoute
        routeQuery.setFeatureWeight(0, 0)
        routeModel.update();
    }

//    gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.FlickGesture | MapGestureArea.PinchGesture
//    gesture.flickDeceleration: 3000
//    gesture.enabled: true

    onCenterChanged:{
        scaleTimer.restart()
        zoomSlider.value = map.zoomLevel
    }

    onZoomLevelChanged:{
        scaleTimer.restart()
    }

    onWidthChanged:{
        scaleTimer.restart()
    }

    onHeightChanged:{
        scaleTimer.restart()
    }

    Component.onCompleted: {
        markers = new Array();
    }

    onShowMainMenu: mapPopupMenu.show(coordinate)
    onShowMarkerMenu: markerPopupMenu.show(coordinate)
    onShowRouteList: stackView.showRouteListPage()
//        activeMapType: MapType.TerrainMap
//        activeMapType: map.supportedMapTypes[6]
//    activeMapType: MapType.HybridMap

    center {
//            latitude: myLatitude
//            longitude: myLongitude
        latitude: 53.931052
        longitude: 27.634170
    }
    zoomLevel: 16

    MapQuickItem {
        id: myLocation
//            coordinate: QtPositioning.coordinate(myLatitude, myLongitude)
        coordinate: QtPositioning.coordinate(53.931052, 27.634170)
        sourceItem: Image {
            id: myLocationImg; source: "resources/location.png"
        }
        anchorPoint: Qt.point(myLocationImg.width/2, myLocationImg.height)
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


    MouseArea {
        id: mouseArea
        property variant lastCoordinate
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onPressed : {
            mouseArea.preventStealing = false
            map.lastX = mouse.x
            map.lastY = mouse.y
            map.pressX = mouse.x
            map.pressY = mouse.y
            lastCoordinate = map.toCoordinate(Qt.point(mouse.x, mouse.y))
        }

        onPositionChanged: {
            if (mouse.button == Qt.LeftButton) {
                map.lastX = mouse.x
                map.lastY = mouse.y
            }
        }

        onDoubleClicked: {
            var mouseGeoPos = map.toCoordinate(Qt.point(mouse.x, mouse.y));
            var preZoomPoint = map.fromCoordinate(mouseGeoPos, false);
            if (mouse.button === Qt.LeftButton) {
                map.zoomLevel++;
            } else if (mouse.button === Qt.RightButton) {
                map.zoomLevel--;
            }
            var postZoomPoint = map.fromCoordinate(mouseGeoPos, false);
            var dx = postZoomPoint.x - preZoomPoint.x;
            var dy = postZoomPoint.y - preZoomPoint.y;

            var mapCenterPoint = Qt.point(map.width / 2.0 + dx, map.height / 2.0 + dy);
            map.center = map.toCoordinate(mapCenterPoint);

            lastX = -1;
            lastY = -1;
        }

        onPressAndHold:{
            mouseArea.preventStealing = true
            if (Math.abs(map.pressX - mouse.x ) < map.jitterThreshold
                    && Math.abs(map.pressY - mouse.y ) < map.jitterThreshold) {
                showMainMenu(lastCoordinate);
            }
        }
        onReleased:  {
            mouseArea.preventStealing = true
        }
    }
    MapPopupMenu {
        id: mapPopupMenu

        function show(coordinate)
        {
            stackView.pop(page)
            mapPopupMenu.coordinate = coordinate
            mapPopupMenu.markersCount = map.markers.length
            mapPopupMenu.update()
            mapPopupMenu.popup()
        }

        onItemClicked: {
            stackView.pop(page)
            switch (item) {
            case "addMarker":
                map.addMarker()
                break
            case "getCoordinate":
                map.coordinatesCaptured(coordinate.latitude, coordinate.longitude)
                break
            case "deleteMarkers":
                map.deleteMarkers()
                break
            default:
                console.log("Unsupported operation")
            }
        }
    }

    MarkerPopupMenu {
        id: markerPopupMenu

        function show(coordinate)
        {
            stackView.pop(page)
            markerPopupMenu.markersCount = map.markers.length
            markerPopupMenu.update()
            markerPopupMenu.popup()
        }

        onItemClicked: {
            stackView.pop(page)
            switch (item) {
            case "deleteMarker":
                map.deleteMarker(map.currentMarker)
                break;
            case "getMarkerCoordinate":
                map.coordinatesCaptured(map.markers[map.currentMarker].coordinate.latitude, map.markers[map.currentMarker].coordinate.longitude)
                break;
            case "routeToNextPoint":
            case "routeToNextPoints":
                map.calculateMarkerRoute()
                break
            case "distanceToNextPoint":
                var coordinate1 = map.markers[currentMarker].coordinate;
                var coordinate2 = map.markers[currentMarker+1].coordinate;
                var distance = Helper.formatDistance(coordinate1.distanceTo(coordinate2));
                stackView.showMessage(qsTr("Distance"),"<b>" + qsTr("Distance:") + "</b> " + distance)
                break
            default:
                console.log("Unsupported operation")
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        focus: true
        initialItem: Item {
            id: page
        }

        function showMessage(title,message,backPage)
        {
            push({ item: Qt.resolvedUrl("forms/Message.qml") ,
                               properties: {
                                   "title" : title,
                                   "message" : message,
                                   "backPage" : backPage
                               }})
            currentItem.closeForm.connect(closeMessage)
        }

        function closeMessage(backPage)
        {
            pop(backPage)
        }

        function closeForm()
        {
            pop(page)
        }

        function showRouteListPage()
        {
            push({ item: Qt.resolvedUrl("RouteList.qml") ,
                               properties: {
                                   "routeModel" : map.routeModel
                               }})
            currentItem.closeForm.connect(closeForm)
        }
    }

    RouteModel {
        id: routeModel
        plugin : map.plugin
        query:  RouteQuery {
            id: routeQuery
        }
        onStatusChanged: {
            if (status == RouteModel.Ready) {
                switch (count) {
                case 0:
                    // technically not an error
                    map.routeError()
                    break
                case 1:
                    map.showRouteList()
                    break
                }
            } else if (status == RouteModel.Error) {
                map.routeError()
            }
        }
    }
    //! [routemodel0]

    //! [routedelegate0]
    Component {
        id: routeDelegate

        MapRoute {
            id: route
            route: routeData
            line.color: "#46a2da"
            line.width: 5
            smooth: true
            opacity: 0.8
     //! [routedelegate0]
            MouseArea {
                id: routeMouseArea
                anchors.fill: parent
                hoverEnabled: false
                property variant lastCoordinate

                onPressed : {
                    map.lastX = mouse.x + parent.x
                    map.lastY = mouse.y + parent.y
                    map.pressX = mouse.x + parent.x
                    map.pressY = mouse.y + parent.y
                    lastCoordinate = map.toCoordinate(Qt.point(mouse.x, mouse.y))
                }

                onPositionChanged: {
                    if (mouse.button == Qt.LeftButton) {
                        map.lastX = mouse.x + parent.x
                        map.lastY = mouse.y + parent.y
                    }
                }

                onPressAndHold:{
                    if (Math.abs(map.pressX - parent.x- mouse.x ) < map.jitterThreshold
                            && Math.abs(map.pressY - parent.y - mouse.y ) < map.jitterThreshold) {
                        showRouteMenu(lastCoordinate);
                    }
                }

            }
    //! [routedelegate1]
        }
    }

    MapItemView {
        model: routeModel
        delegate: routeDelegate
    //! [routeview0]
        autoFitViewport: true
    //! [routeview1]
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
