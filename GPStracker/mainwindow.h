#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql>
#include <QtWidgets>
#include <QtSerialPort/QSerialPort>
#include <QtPositioning>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow();
private:
    QSqlDatabase* db;
    QSerialPort* serial;
    QTextEdit* textEdit;
    QTextEdit* textEdit2;
    QComboBox* portName;
    QComboBox* baudRate;
    QPushButton* openPortButton;
    QPushButton* closePortButton;
    QTimer* timer;
    int id;
//    QNmeaPositionInfoSource *nmeaSource;

    void parseInput();
private slots:
    void openSerialPort();
    void closeSerialPort();
    void readData();

//    void positionUpdated(const QGeoPositionInfo &info);
};

#endif // MAINWINDOW_H
