#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T09:48:47
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGIS
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

QGIS_DIR = C:/Program Files/QGIS 2.16/qgis-2.16.2/src

INCLUDEPATH += $$QGIS_DIR/src/core
INCLUDEPATH += $$QGIS_DIR/src/gui
