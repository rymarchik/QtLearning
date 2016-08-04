#include "rageCounter.h"

RageCounter::RageCounter(QWidget *parent)
    : QWidget(parent)
{
    scaleName = new QLabel("Опоздание на работу");
    rageName = new QLabel("Реакция НВ");
    rageOutput = new QLabel;
    rageOutput->setPixmap(QPixmap(":/happy.png"));

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0,20);
    slider->setSingleStep(2);
    slider->setValue(0);
    slider->setTickInterval(2);
    slider->setTickPosition(QSlider::TicksBelow);

    connect(slider, SIGNAL(valueChanged(int)), SLOT(sliderChange(int)));

    QGridLayout* grid = new QGridLayout;
    grid->addWidget(scaleName,0,0);
    grid->addWidget(rageName,0,1);
    grid->addWidget(slider,1,0);
    grid->addWidget(rageOutput,1,1);
    grid->setMargin(20);
    grid->setSpacing(50);
    setLayout(grid);

    resize(500,200);
    setWindowTitle(tr("Slider of wraith"));
}

void RageCounter::sliderChange(int counter) {
    scaleName->setText("Опоздание на " + QString::number(counter) + " мин");

    if (counter == 0) {
        rageOutput->setPixmap(QPixmap(":/happy.png"));
        scaleName->setText("Не опоздал, ну ничего себе!");
    }
    else if (counter >= 2 && counter < 10)
        rageOutput->setPixmap(QPixmap(":/poker.png"));
    else if (counter >= 10 && counter < 20)
        rageOutput->setPixmap(QPixmap(":/angry.png"));
    else if (counter == 20)
        rageOutput->setPixmap(QPixmap(":/rage.png"));
}
