#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QtWidgets>

class Server : public QWidget
{
    Q_OBJECT
private:
    QTcpServer* server;
    QTextEdit* text;
    quint16 blockSize;
private:
    void sendToClient(QTcpSocket* socket, const QString& str);
public:
    Server(int port);
public slots:
    virtual void slotNewConnection();
    void slotReadClient();
};

#endif // SERVER_H
