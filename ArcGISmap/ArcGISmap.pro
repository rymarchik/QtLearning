CONFIG += c++11 arcgis_runtime_qml10_2_6

QT += core gui opengl xml network script positioning sensors
QT += qml quick

TEMPLATE = app
TARGET = ArcGISProject

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
