#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T11:19:43
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCPServer
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp\

HEADERS  += server.h

QMAKE_LFLAGS += -static -static-libgcc
