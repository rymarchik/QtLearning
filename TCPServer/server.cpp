#include "server.h"

Server::Server(int port)
    : QWidget()
    , blockSize(0)
{
    server = new QTcpServer(this);
    if (!server->listen(QHostAddress::Any, port)) {
        QMessageBox::critical(0, "Server name", "Unable to start the server" + server->errorString());
        server->close();
        return;
    }
    connect(server, SIGNAL(newConnection()), SLOT(slotNewConnection()));

    text = new QTextEdit;
    text->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(new QLabel("<h1>Server</h1>"));
    layout->addWidget(text);

    setLayout(layout);
}

void Server::slotNewConnection() {
    QTcpSocket* socket = server->nextPendingConnection();
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadClient()));
    sendToClient(socket, "Server: connected!");
}

void Server::slotReadClient() {
    QTcpSocket* socket = (QTcpSocket*)sender();
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

        QString message = time.toString() + " " + "Client has sent - " + str;
        text->append(message);

        blockSize = 0;
        sendToClient(socket, "Server: received \"" + str + "\"");
    }
}

void Server::sendToClient(QTcpSocket* socket, const QString& str) {
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    socket->write(arrBlock);
}
