import QtQuick 2.5
import QtQuick.Controls 1.4

Menu {
    signal itemClicked(string item)

    function update() {
        clear()
        addItem(qsTr("Info")).triggered.connect(function(){itemClicked("showRouteInfo")})
        addItem(qsTr("Delete")).triggered.connect(function(){itemClicked("deleteRoute")})
    }
}
