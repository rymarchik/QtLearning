import QtQuick 2.5
import QtQuick.Controls 1.4
import QtLocation 5.6

MenuBar {
    property variant toolsMenu: toolsMenu

    signal selectTool(string tool);

    Menu {
        id: toolsMenu
        title: qsTr("Tools")

        function createMenu(map)
        {
            clear()
            if (map.plugin.supportsRouting()) {
                addItem(qsTr("Route with coordinates")).triggered.connect(function(){selectTool("CoordinateRoute")})
            }
        }
    }
}
