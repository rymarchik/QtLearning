#include "mainwindow.h"

MainWindow::MainWindow()
{
    serial = new QSerialPort(this);
//    nmeaSource = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode);
//    nmeaSource->setDevice(serial);
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("A200");
    db.setUserName("asrymarchik");
    db.setPassword("123456");
    db.setHostName("192.168.1.42");
    db.setPort(5432);
    db.open();

    textEdit = new QTextEdit;
    textEdit2 = new QTextEdit;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(textEdit2);

    portName = new QComboBox;
    QStringList list1;
    list1 << "COM2" << "COM1" << "COM3";
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
    mainlayout->addLayout(layout);
    mainlayout->addLayout(layout2);

    timer = new QTimer;
    id = 1;

    connect(openPortButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(closePortButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(timer, SIGNAL(timeout()), this, SLOT(readData()));
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
        timer->start(1000);
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
        timer->stop();
    }
}

void MainWindow::readData() {
    QString data = serial->readAll();
    textEdit->setText(data);
    parseInput();
}

void MainWindow::parseInput() {
    QRegExp ggaRegExp("(GP|GN|GL)GGA", Qt::CaseInsensitive);
    QRegExp timeRegExp("(\\d{6})(\\.\\d+)", Qt::CaseInsensitive);
    QRegExp latRegExp("(\\d{2})(\\d{2}\\.\\d+)", Qt::CaseInsensitive);
    QRegExp lonRegExp("(\\d{3})(\\d{2}\\.\\d+)", Qt::CaseInsensitive);
    QSqlQuery query;
    QDateTime time;
    double latitude;
    double longitude;
    double altitude;

    QString line = textEdit->toPlainText();
    QStringList lines = line.split('$');

    foreach (line, lines) {
        QStringList fields = line.split(",");

        if (fields[0].contains(ggaRegExp)) {
            if (fields[1].contains(timeRegExp)) {
                int timeint = timeRegExp.cap(1).toInt();
                time = QDateTime::fromString(QString::number(timeint), "hhmmss");
                time.setTimeSpec(Qt::UTC);
            }
            if (fields[2].contains(latRegExp)) {
                int deg = latRegExp.cap(1).toInt();
                double min = latRegExp.cap(2).toDouble();
                latitude = deg+min/60.0;
            }
            if(fields[3] == "S") {
                latitude *= -1;
            }
            if(fields[4].contains(lonRegExp)) {
                int deg = lonRegExp.cap(1).toInt();
                double min = lonRegExp.cap(2).toDouble();
                longitude = deg+min/60.0;
            }
            if(fields[5] == "W") {
                longitude *= -1;
            }
            altitude = fields[9].toDouble();

//            m_items.correction_mode = fields[6].toInt();
//            m_items.sat_used = fields[7].toInt();
//            m_items.hdop = fields[8].toDouble(); //Set both here and in GSA
//            m_items.geo_sep = fields[9].toDouble();
//            m_items.height = fields[11].toDouble() + m_items.geo_sep;
//            m_items.correction_age = fields[13].toDouble();
//            fields[14].chop(3); //remove *FF checksum from the end
//            m_items.lband_chan_num = fields[14].toInt();
        }
    }
    textEdit2->append("Время: " + time.toLocalTime().toString("hh:mm:ss") + "\tШирота: " +
                      QString::number(latitude) + "\tДолгота: " + QString::number(longitude) +
                      "\tВысота над уровнем моря: " + QString::number(altitude));

    QString insertRow = "INSERT INTO location (id, latitude, longitude, altitude, time)"
                         " VALUES (%1, %2, %3, %4, '%5');";
    QString deleteRow = "DELETE FROM location WHERE id = 1";

    if (id == 11) {
        if (!query.exec(deleteRow)) {
            qDebug() << "Unable to delete row";
        }
        id = 1;
    }

    QString str = insertRow.arg(id).arg(latitude).arg(longitude).arg(altitude).arg(time.toString("hh:mm:ss"));
    if (!query.exec(str)) {
        qDebug() << "Unable to make insert operation";
    }
    id++;
}

//void MainWindow::positionUpdated(const QGeoPositionInfo &info) {
//    textEdit->append("position changed");
//    textEdit->append(QString("Lat: %1").arg(QString::number(info.coordinate().latitude())));
//    textEdit->append(QString("Lon: %1").arg(QString::number(info.coordinate().longitude())));
//}
