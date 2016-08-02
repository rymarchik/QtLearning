#include "widget.h"
#include <QtWidgets>
using namespace Qt;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget button;

    QWidget* wgt = new QWidget;
    qDebug() << wgt->width();
    wgt->setWindowFlags(Window);
    wgt->setWindowTitle("Main window!");
//    wgt.resize(1000,500);

    qDebug() << wgt->x() << wgt->y();
    wgt->move(0,100);
    qDebug() << wgt->x() << wgt->y();

    wgt->setGeometry(555,222,1000,400);

    qDebug() << wgt->x() << wgt->y();

    QPalette pal;
    pal.setColor(wgt->backgroundRole(), red);
    wgt->setPalette(pal);

    QWidget* wgt2 = new QWidget(wgt);
    QPalette pal2;
    pal2.setColor(wgt2->backgroundRole(), blue);
    wgt2->setPalette(pal2);
    wgt2->setAutoFillBackground(true);
//    wgt2->setGeometry(0,0,500,250);
    QLabel* label = new QLabel("&Синий квадратик:");
    label->setBuddy(wgt2);

    QWidget* wgt3 = new QWidget(wgt);
    QPalette pal3;
    QPixmap pix(":/cat.jpg");
    pal3.setBrush(wgt3->backgroundRole(), QBrush(pix));
    wgt3->setPalette(pal3);
    wgt3->setAutoFillBackground(true);
//    wgt3->setGeometry(500,0,500,250);

    QPixmap pic(":/doge.jpg");
    QCursor cur(pic);
    wgt3->setCursor(cur);

//    QFrame* frame = new QFrame(&wgt);
//    frame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
//    frame->setLineWidth(5);
//    frame->show();

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->setMargin(20);
    hlayout->setSpacing(50);
    hlayout->addWidget(wgt2, 1);
//    hlayout->addSpacing(50);
//    hlayout->addStretch(1);
    hlayout->addWidget(wgt3, 3);

    QVBoxLayout* vlayout = new QVBoxLayout;
    QPushButton* b1 = new QPushButton("Нажми на меня");
    QPushButton* b2 = new QPushButton("а теперь на меня");
    vlayout->addWidget(b1);
    vlayout->addWidget(b2);
    vlayout->addLayout(hlayout);

    wgt->setLayout(vlayout);

    QScrollArea scr;
    scr.setWidget(wgt);
    scr.resize(wgt->width() + 30, wgt->height() - 150);
//    qDebug() << scr.height() << scr.width();

    scr.show();

    QObject::connect(b1, SIGNAL(clicked(bool)), &button, SLOT(b1click()));
    QObject::connect(b2, SIGNAL(clicked(bool)), &button, SLOT(b2click()));

    return a.exec();
}
