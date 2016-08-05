#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client("localhost", 2323);
    client.show();

    return a.exec();
}
