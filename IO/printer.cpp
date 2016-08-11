#include "printer.h"

Printer::Printer(QWidget *parent)
    : QWidget(parent)
{
}

void Printer::print(QIODevice* dev) {
    char ch;
    QString str;

    dev->open(QIODevice::ReadOnly);
    while (!dev->atEnd()) {
        dev->getChar(&ch);
        str += ch;
    }
    dev->close();
    qDebug() << str;
}
