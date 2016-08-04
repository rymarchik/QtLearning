#include "lineEdit.h"

LineEdit::LineEdit(QWidget *parent)
    : QWidget(parent)
{
    display = new QLabel;
    display->setFrameStyle(QFrame::Box | QFrame::Raised);
    display->setLineWidth(3);
    display->setFixedHeight(50);

    textlbl = new QLabel("Text");
    text = new QLineEdit;
    connect(text, SIGNAL(textChanged(QString)), display, SLOT(setText(QString)));

    passlbl = new QLabel("&Password");
    pass = new QLineEdit;
    pass->setEchoMode(QLineEdit::Password);
    passlbl->setBuddy(pass);
    connect(pass, SIGNAL(textChanged(QString)), display, SLOT(setText(QString)));

    QVBoxLayout* vlay = new QVBoxLayout;
    vlay->addWidget(display);
    vlay->addWidget(textlbl);
    vlay->addWidget(text);
    vlay->addWidget(passlbl);
    vlay->addWidget(pass);

    setLayout(vlay);
}
