#include "mainwindow.h"
#include <QApplication>
//#include <QQuickView>
#include <QGuiApplication>
//#include <QQmlEngine>

//#include <QtPlugin>

//QT_BEGIN_NAMESPACE
//Q_IMPORT_PLUGIN(qjpeg)
//Q_IMPORT_PLUGIN(qgif)
//Q_IMPORT_PLUGIN(qkrcodecs)
//QT_END_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();   

    return a.exec();
}
