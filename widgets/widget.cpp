#include "widget.h"
#include "ui_widget.h"


widget::widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
}

widget::~widget()
{
    delete ui;
}


void widget::b1click() {
    QMessageBox::information(this, "кнопочка 1", "ыть");
}

void widget::b2click() {
    QMessageBox::information(this, "кнопочка 2", "а тут пусто:(");
}
