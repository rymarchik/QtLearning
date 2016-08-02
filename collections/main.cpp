//#include "mainwindow.h"
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<QString> list;

    list << "123" << "456" << "789";
    QMutableListIterator<QString> iter(list);
    while (iter.hasNext()) {
        qDebug() << iter.next();
    }

    QMap<int, QString> map;
    map.insert(1, "2");
    map.insert(2, "3");
    QMap<int,QString>::iterator it = map.begin();
    for(; it != map.end(); ++it)
        qDebug() << it.key() << it.value();

    QVariant v("string");
    qDebug() << QVariant::typeToName(v.type());
    qDebug() << v.type();

    return a.exec();
}
