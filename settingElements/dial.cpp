#include "dial.h"

Dial::Dial() : QWidget() {
    dial = new QDial;
    prb = new QProgressBar;

    dial->setRange(0,100);
    dial->setNotchTarget(5);
    dial->setNotchesVisible(true);
    dial->setWrapping(true);

    connect(dial, SIGNAL(valueChanged(int)), prb, SLOT(setValue(int)));

    QVBoxLayout* vlay = new QVBoxLayout;
    vlay->addWidget(dial);
    vlay->addWidget(prb);

    setLayout(vlay);
    resize(200,200);
}
