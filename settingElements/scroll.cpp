#include <scroll.h>

Scroll::Scroll() : QWidget() {
    lcd = new QLCDNumber(3);
    scr = new QScrollBar(Qt::Horizontal);

    connect(scr, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));

    QVBoxLayout* vlay = new QVBoxLayout;
    vlay->addWidget(lcd);
    vlay->addWidget(scr);

    setLayout(vlay);
    resize(250,150);
}
