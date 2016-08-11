#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T14:52:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IO
TEMPLATE = app


SOURCES += main.cpp \
    printer.cpp \
    fileFinder.cpp \
    fileWatcher.cpp

HEADERS  += \
    printer.h \
    fileFinder.h \
    fileWatcher.h

RESOURCES += \
    files.qrc
