#ifndef WIDGET_H
#define WIDGET_H
#include "QMessageBox"
#include <QMainWindow>

namespace Ui {
class widget;
}

class widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = 0);
    ~widget();

private:
    Ui::widget *ui;

private slots:
    void b1click();
    void b2click();
};

#endif // WIDGET_H
