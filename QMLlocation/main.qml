import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Elements location")

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        Rectangle {
            Layout.fillHeight: true
            Layout.minimumHeight: 64
            Layout.minimumWidth: 64
            color: "red"
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumHeight: 64
            Layout.minimumWidth: 64
            color: "blue"
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.minimumHeight: 64
            Layout.minimumWidth: 64
            color: "green"
        }
    }

    GridLayout {
        anchors.centerIn: parent
        rows: 2
        columns: 2

        Rectangle {
            color: "red"; width: 64; height: 64;
        }
        Rectangle {
            color: "yellow"; width: 64; height: 64;
        }
        Rectangle {
            color: "green"; width: 64; height: 64;
        }
        Rectangle {
            color: "black"; width: 64; height: 64;
        }
    }
}
