#include "rageCounter.h"
#include "scroll.h"
#include "dial.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RageCounter r;
    Scroll scr;
    Dial d;

    QSplitter* sp = new QSplitter(Qt::Vertical);
    sp->addWidget(&r);
    sp->addWidget(&scr);
    sp->addWidget(&d);

    sp->setGeometry(500, 300, 500, 550);
    sp->show();

    return a.exec();
}
