import QtQuick 2.5
import QtQuick.Controls 1.4
import QtLocation 5.6
import QtPositioning 5.5
import "map"
import "menus"
import "helper.js" as Helper

ApplicationWindow {
    id: appWindow
    property variant map
    property variant parameters

    property variant fromCoordinate: QtPositioning.coordinate(53.931052, 27.634170)
    property variant toCoordinate: QtPositioning.coordinate(59.9645, 10.671)

    signal selectProvider(string providerName)

    function createMap(provider)
    {
        var plugin = Qt.createQmlObject ('import QtLocation 5.6; Plugin{ name:"' + provider + '"; parameters: appWindow.parameters}', appWindow)

        var zoomLevel = null
        var center = null
        if (map) {
            zoomLevel = map.zoomLevel
            center = map.center
            map.destroy()
        }

        map = mapComponent.createObject(page);
        map.plugin = plugin;
        if (zoomLevel != null) {
            map.zoomLevel = zoomLevel
            map.center = center
        } else {
            map.zoomLevel = (map.maximumZoomLevel - map.minimumZoomLevel)/2
        }

        map.forceActiveFocus()
    }

    function initializeProvider()
    {
        var parameters = new Array()
        var app_id = Qt.createQmlObject('import QtLocation 5.6; PluginParameter {name: "here.app_id"; value: "bPTNwzHlkiS3xScHR1yO"}',appWindow)
        var token = Qt.createQmlObject('import QtLocation 5.6; PluginParameter {name: "here.token"; value: "BX9WhKp3gZiNa2J4chisQQ"}',appWindow)
        var map_id = Qt.createQmlObject('import QtLocation 5.6; PluginParameter {name: "mapbox.map_id"; value: "insurg.2itw2fj3"}',appWindow)
        var access_token = Qt.createQmlObject('import QtLocation 5.6; PluginParameter {name: "mapbox.access_token"; value: "pk.eyJ1IjoiaW5zdXJnIiwiYSI6ImNpdHh6Mno5eDAwM3Yybms5bmE1c2xuNHoifQ.vtH2RrfMDazayR93b3qidw"}',appWindow)
        parameters.push(app_id)
        parameters.push(token)
        appWindow.parameters = parameters
        var plugin = Qt.createQmlObject ('import QtLocation 5.6; Plugin {name: "here"}', appWindow)
        selectProvider(plugin.name)
    }

    title: qsTr("Mapviewer")
    height: 640
    width: 800
    visible: true
    menuBar: mainMenu

    onSelectProvider: {
        stackView.pop()
        createMap(providerName)
        if (map.error === Map.NoError) {
            map.activeMapType = map.supportedMapTypes[MapType.SatelliteMapDay]
            mainMenu.toolsMenu.createMenu(map);
        } else {
            mainMenu.toolsMenu.clear();
        }
    }

    MainMenu {
        id: mainMenu
        onSelectTool: {
            switch (tool) {
            case "CoordinateRoute":
                stackView.pop({item:page, immediate: true})
                stackView.push({ item: Qt.resolvedUrl("forms/RouteCoordinate.qml") ,
                                   properties: { "toCoordinate": toCoordinate,
                                       "fromCoordinate": fromCoordinate}})
                stackView.currentItem.showRoute.connect(map.calculateCoordinateRoute)
                stackView.currentItem.closeForm.connect(stackView.closeForm)
                break
            default:
                console.log("Unsupported operation")
            }
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
            case "fitViewport":
                map.fitViewportToMapItems()
                break
            case "deleteMarkers":
                map.deleteMarkers()
                break
            case "deleteItems":
                map.deleteMapItems()
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

    ItemPopupMenu {
        id: itemPopupMenu

        function show(coordinate)
        {
            stackView.pop(page)
            itemPopupMenu.update()
            itemPopupMenu.popup()
        }

        onItemClicked: {
            stackView.pop(page)
            switch (item) {
            case "showRouteInfo":
                stackView.showRouteListPage()
                break;
            case "deleteRoute":
                map.routeModel.reset();
                break;
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
            push({ item: Qt.resolvedUrl("forms/RouteList.qml") ,
                               properties: {
                                   "routeModel" : map.routeModel
                               }})
            currentItem.closeForm.connect(closeForm)
        }
    }

    Component {
        id: mapComponent

        MapComponent{
            width: page.width
            height: page.height
            onCoordinatesCaptured: {
                var text = "<b>" + qsTr("Latitude:") + "</b> " + Helper.roundNumber(latitude,4) + "<br/><b>" + qsTr("Longitude:") + "</b> " + Helper.roundNumber(longitude,4)
                stackView.showMessage(qsTr("Coordinates"),text);
            }
            onRouteError: stackView.showMessage(qsTr("Route Error"),qsTr("Unable to find a route for the given points"),page)
            onShowMainMenu: mapPopupMenu.show(coordinate)
            onShowMarkerMenu: markerPopupMenu.show(coordinate)
            onShowRouteMenu: itemPopupMenu.show(coordinate)
            onShowRouteList: stackView.showRouteListPage()
        }
    }
}
