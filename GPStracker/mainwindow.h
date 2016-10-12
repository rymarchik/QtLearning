#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql>
#include <QtWidgets>
#include <QtSerialPort/QSerialPort>
#include <QtPositioning>
#include <QtQuickWidgets>
#include <QProcess>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow();
private:
    QSqlDatabase db;
    QSerialPort* serial;

    QQuickWidget* qmlwgt;
    QQmlContext* contxt;
    QTextEdit* textEdit;

    QComboBox* portName;
    QComboBox* baudRate;
    QPushButton* openPortButton;
    QPushButton* closePortButton;

    QTimer* timer;
    int id;
//    QNmeaPositionInfoSource *nmeaSource;
    QPushButton* openQGISButton;
    QProcess* proc;


private slots:
    void openSerialPort();
    void closeSerialPort();
//    void readData();
    void parseInput();
    void openQGIS();

//    void positionUpdated(const QGeoPositionInfo &info);
};

#endif // MAINWINDOW_H
