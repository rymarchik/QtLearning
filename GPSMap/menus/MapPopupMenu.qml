import QtQuick 2.5
import QtQuick.Controls 1.4

Menu {
    property variant coordinate
    property int markersCount
    signal itemClicked(string item)

    function update() {
        clear()
        addItem(qsTr("Add Marker")).triggered.connect(function(){itemClicked("addMarker")})
        addItem(qsTr("Get coordinate")).triggered.connect(function(){itemClicked("getCoordinate")})
        addItem(qsTr("Fit Viewport To Map Items")).triggered.connect(function(){itemClicked("fitViewport")})

        if (markersCount > 0) {
            addItem(qsTr("Delete all markers")).triggered.connect(function(){itemClicked("deleteMarkers")})
        }
    }
}
