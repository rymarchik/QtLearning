#include "progress.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Progress prog;
    QWidget wgt;

    QLabel* lbl = new QLabel("&Decimal value:");
    QSpinBox* box = new QSpinBox;
    box->setMaximum(1000);
    lbl->setBuddy(box);

    QLCDNumber* lcd = new QLCDNumber(12);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setBinMode();
    QLabel* lbl2 = new QLabel("Binary value:");
    QObject::connect(box, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));

    QLabel* lblurl = new QLabel("<a href=\"http://img12.nnm.me/7/b/a/8/7/7ba875b7bd80980f79ac6cae68418e77_full.jpg\">Нажми-ка!</a>");
    lblurl->setOpenExternalLinks(true);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(lbl);
    layout->addWidget(box);
    layout->addWidget(lbl2);
    layout->addWidget(lcd);
    layout->addWidget(lblurl);
    wgt.setLayout(layout);

    QSplitter split(Qt::Horizontal);
    split.addWidget(&prog);
    split.addWidget(&wgt);
    split.setGeometry(500,300,444,200);

    split.show();

    return a.exec();
}
