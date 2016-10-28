import QtQuick 2.5
import QtQuick.Controls 1.4

Menu {
    property int currentMarker
    property int markersCount
    signal itemClicked(string item)

    function update() {
        clear()
        addItem(qsTr("Delete")).triggered.connect(function(){itemClicked("deleteMarker")})
        addItem(qsTr("Coordinates")).triggered.connect(function(){itemClicked("getMarkerCoordinate")})
        if (currentMarker == markersCount-2){
            addItem(qsTr("Route to next point")).triggered.connect(function(){itemClicked("routeToNextPoint")});
            addItem(qsTr("Distance to next point")).triggered.connect(function(){itemClicked("distanceToNextPoint")});
        }
        if (currentMarker < markersCount-2){
            addItem(qsTr("Route to next points")).triggered.connect(function(){itemClicked("routeToNextPoints")});
            addItem(qsTr("Distance to next point")).triggered.connect(function(){itemClicked("distanceToNextPoint")});
        }
    }
}
