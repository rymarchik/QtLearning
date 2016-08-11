#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QIODevice>

class Printer : public QWidget
{
    Q_OBJECT

public:
    Printer(QWidget *parent = 0);
    void print(QIODevice* dev);
};

#endif // WIDGET_H
