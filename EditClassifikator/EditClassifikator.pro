#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T10:54:15
#
#-------------------------------------------------

QT       += core gui sql

#QMAKE_LFLAGS_RELEASE += -static -static-libgcc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EditClassifikator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dlgdialog.cpp

HEADERS  += mainwindow.h \
    dlgdialog.h

FORMS    += mainwindow.ui \
    dlgdialog.ui

RESOURCES += \
    editclassifikator.qrc

QMAKE_LFLAGS += -static -static-libgcc

#QTPLUGIN     += qjpeg \
#                         qgif \
#                         qkrcodecs
