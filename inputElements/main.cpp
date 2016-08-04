#include "lineEdit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LineEdit l;
    l.show();

    return a.exec();
}
