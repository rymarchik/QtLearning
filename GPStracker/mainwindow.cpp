#include "mainwindow.h"

MainWindow::MainWindow()
{
    serial = new QSerialPort(this);
//    nmeaSource = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode);
//    nmeaSource->setDevice(serial);

    textEdit = new QTextEdit;
    portName = new QComboBox;
    QStringList list1;
    list1 << "COM1" << "COM2" << "COM3";
    portName->addItems(list1);
    baudRate = new QComboBox;
    QStringList list2;
    list2 << "115200" << "4800";
    baudRate->addItems(list2);
    openPortButton = new QPushButton("Open port");
    closePortButton = new QPushButton("Close port");
    QVBoxLayout* layout2 = new QVBoxLayout;
    layout2->addWidget(portName);
    layout2->addWidget(baudRate);
    layout2->addWidget(openPortButton);
    layout2->addWidget(closePortButton);

    QHBoxLayout* mainlayout = new QHBoxLayout;
    mainlayout->addWidget(textEdit);
    mainlayout->addLayout(layout2);

    connect(openPortButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(closePortButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
//    connect(nmeaSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));

    setLayout(mainlayout);
    resize(1000,400);
}

void MainWindow::openSerialPort() {
    serial->setPortName(portName->currentText());
    serial->setBaudRate(baudRate->currentText().toInt());
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    if (serial->open(QIODevice::ReadOnly)) {
        textEdit->append("Connected!");
//        nmeaSource->startUpdates();
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        textEdit->append("Open error!");
    }
}

void MainWindow::closeSerialPort() {
    if (serial->isOpen()) {
//        nmeaSource->stopUpdates();
        serial->close();
        textEdit->append("Disconnected!");
    }
}

void MainWindow::readData() {
    QByteArray data = serial->readAll();
    textEdit->append(data);
}

//void MainWindow::positionUpdated(const QGeoPositionInfo &info) {
//    textEdit->append("position changed");
//    textEdit->append(QString("Lat: %1").arg(QString::number(info.coordinate().latitude())));
//    textEdit->append(QString("Lon: %1").arg(QString::number(info.coordinate().longitude())));
//}
