#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

class LineEdit : public QWidget
{
    Q_OBJECT

public:
    LineEdit(QWidget *parent = 0);
private:
    QLabel* display;
    QLabel* textlbl;
    QLabel* passlbl;
    QLineEdit* text;
    QLineEdit* pass;

};

#endif // WIDGET_H
