#include "progress.h"

Progress::Progress(QWidget *parent)
    : QWidget(parent)
    , step(0)
{
    bar = new QProgressBar;
    bar->setRange(0,5);
    bar->setOrientation(Qt::Vertical);
    bar->setMinimumHeight(100);

    QPushButton* stepButton = new QPushButton("&step");
    QPushButton* resetButton = new QPushButton("&reset");

    QObject::connect(stepButton, SIGNAL(clicked()), this, SLOT(slotStep()));
    QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(slotReset()));

    QVBoxLayout* vLay = new QVBoxLayout;
    vLay->addWidget(stepButton);
    vLay->addWidget(resetButton);
    QHBoxLayout* hLay = new QHBoxLayout;
    hLay->addLayout(vLay);
    hLay->addWidget(bar);

    setLayout(hLay);
}

void Progress::slotStep() {
    bar->setValue(++step);
}

void Progress::slotReset() {
    step = 0;
    bar->reset();
}
