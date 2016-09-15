#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtSerialPort/QSerialPort>
#include <QtPositioning>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow();
private:
    QSerialPort* serial;
    QTextEdit* textEdit;
    QComboBox* portName;
    QComboBox* baudRate;
    QPushButton* openPortButton;
    QPushButton* closePortButton;
//    QNmeaPositionInfoSource *nmeaSource;
private slots:
    void openSerialPort();
    void closeSerialPort();
    void readData();
//    void positionUpdated(const QGeoPositionInfo &info);
};

#endif // MAINWINDOW_H
