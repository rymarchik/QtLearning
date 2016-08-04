#include "groupbox.h"

GroupBox::GroupBox(QWidget *parent)
    : QGroupBox(parent)
{
    setCheckable(true);
    setChecked(true);

    r1 = new QRadioButton("Red");
    r2 = new QRadioButton("Green");
    r3 = new QRadioButton("Blue");
    r1->setChecked(true);
    connect(r1, SIGNAL(clicked()), SLOT(buttonClicked()));
    connect(r2, SIGNAL(clicked()), SLOT(buttonClicked()));
    connect(r3, SIGNAL(clicked()), SLOT(buttonClicked()));

    c1 = new QCheckBox("Light");
    c1->setChecked(true);
    connect(c1, SIGNAL(clicked()), SLOT(buttonClicked()));

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(r1);
    lay->addWidget(r2);
    lay->addWidget(r3);
    lay->addWidget(c1);
    setLayout(lay);

    setAutoFillBackground(true);
    buttonClicked();
}

void GroupBox::buttonClicked() {
    QPalette pal = palette();
    int brightness = c1->isChecked()? 150: 80;
    if (r1->isChecked()) {
        pal.setColor(backgroundRole(), QColor(Qt::red).light(brightness));
    }
    else if (r2->isChecked()) {
        pal.setColor(backgroundRole(), QColor(Qt::green).light(brightness));
    }
    else {
        pal.setColor(backgroundRole(), QColor(Qt::blue).light(brightness));
    }
    setPalette(pal);
}

//void MainWindow::funny(QPushButton* b) {
//    QPixmap pix(":/doge.jpg");
//    b->setIcon(pix);
//    b->setIconSize(pix.size());
//}

//void MainWindow::sad(QPushButton* b) {
//    QPixmap pix(":/doge.jpg");
//    b->setIcon(pix);
//    b->setIconSize(pix.size());
//}
