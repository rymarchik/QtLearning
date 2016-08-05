#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include <QTcpSocket>

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(const QString& host, int port, QWidget *parent = 0);
private:
    QTcpSocket* socket;
    QTextEdit* info;
    QLineEdit* input;
    quint16 blockSize;
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotSendToServer();
    void slotConnected();
};

#endif // CLIENT_H
