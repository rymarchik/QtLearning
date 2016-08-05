#include "client.h"

Client::Client(const QString &host, int port, QWidget *parent) : QWidget(parent), blockSize(0)
{
    socket = new QTcpSocket(this);

    socket->connectToHost(host, port);
    connect(socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(slotError(QAbstractSocket::SocketError)));

    info = new QTextEdit;
    input = new QLineEdit;

    info->setReadOnly(true);

    QPushButton* button = new QPushButton("&Send");
    connect(button, SIGNAL(clicked()), SLOT(slotSendToServer()));
    connect(input, SIGNAL(returnPressed()), SLOT(slotSendToServer()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(new QLabel("<h1>Client</h1>"));
    layout->addWidget(info);
    layout->addWidget(input);
    layout->addWidget(button);

    setLayout(layout);
}

void Client::slotReadyRead() {
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_7);
    for (;;) {
        if (!blockSize) {
            if(socket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> blockSize;
        }
        if (socket->bytesAvailable() < blockSize) {
            break;
        }
        QTime time;
        QString str;
        in >> time >> str;

        info->append(time.toString() + " " + str);
        blockSize = 0;
    }
}

void Client::slotError(QAbstractSocket::SocketError err) {
    QString error = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host wasn't found." :
                                 err == QAbstractSocket::RemoteHostClosedError ? "The remote host is closed." :
                                 err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused." :
                                 QString(socket->errorString()));
    info->append(error);
}

void Client::slotSendToServer() {
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << quint16(0) << QTime::currentTime() << input->text();

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    socket->write(arrBlock);
    input->setText("");
}

void Client::slotConnected() {
    info->append("Received the connected() signal");
}
