#include "editor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Editor w;
//    Dialog d;
    w.show();

    return a.exec();
}
