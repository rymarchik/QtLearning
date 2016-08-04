#include "groupbox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GroupBox grb;
    GroupBox grb2;
    QWidget wgt;

    QPushButton* b1 = new QPushButton("Normal");
    b1->setDefault(true);

    QPushButton* b2 = new QPushButton("Toggled");
    b2->setCheckable(true);
    b2->setChecked(true);

    QPushButton* b3 = new QPushButton("Flat");
    b3->setFlat(true);

    QPushButton* b4 = new QPushButton("f");
    QPixmap pix(":/cat.jpg");
    b4->setIcon(pix);
    b4->setIconSize(pix.size());
    QMenu* menu = new QMenu(b4);
    menu->addAction("Тыц");
    menu->addAction("Тыц");
    menu->addSeparator();
    menu->addAction("Exit", QApplication::quit);
    b4->setMenu(menu);

    QCheckBox* c1 = new QCheckBox("Normal");
    c1->setChecked(true);

    QCheckBox* c2 = new QCheckBox("Tristate");
    c2->setTristate(true);
    c2->setCheckState(Qt::PartiallyChecked);

    QGridLayout* lay = new QGridLayout;
    lay->addWidget(b1,0,0);
    lay->addWidget(b2,0,1);
    lay->addWidget(b3,1,0);
    lay->addWidget(b4,1,1);
    lay->addWidget(c1,2,0);
    lay->addWidget(c2,2,1);
    wgt.setLayout(lay);

    QSplitter split(Qt::Horizontal);
    split.addWidget(&grb);
    split.addWidget(&wgt);
    split.addWidget(&grb2);
    split.setGeometry(500,300,555,200);

    split.show();

    return a.exec();
}


