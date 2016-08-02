#include "counter.h"
#include <QtWidgets>
#include <QtGlobal>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel lbl("0");

    Counter counter;

    QSignalMapper* mapper = new QSignalMapper();
    QObject::connect(mapper, SIGNAL(mapped(const QString&)), &counter, SLOT(slotInc(const QString&)));

    QPushButton* but1 = new QPushButton("Button1");
    QObject::connect(but1, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but1, "Button1 Action");

    QPushButton* but2 = new QPushButton("Button2");
    QObject::connect(but2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(but2, "Button2 Action");

    QPushButton quitButton("Quit");

    QVBoxLayout layout;
    layout.addWidget(&lbl);
    layout.addWidget(but1);
    layout.addWidget(but2);
    layout.addWidget(&quitButton);

    QWidget window;
    window.setLayout(&layout);
    window.show();

    QObject::connect(&counter, SIGNAL(counterChanged(int)), &lbl, SLOT(setNum(int)));
    QObject::connect(&counter, SIGNAL(goodbye()), &app, SLOT(quit()));
    QObject::connect(&quitButton, SIGNAL(clicked(bool)), &app, SLOT(quit()));

    return app.exec();
}
