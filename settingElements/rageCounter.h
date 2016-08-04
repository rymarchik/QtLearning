#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

class RageCounter : public QWidget
{
    Q_OBJECT

public:
    RageCounter(QWidget *parent = 0);
private:
    QSlider* slider;
    QLabel* scaleName;
    QLabel* rageName;
    QLabel* rageOutput;
signals:
    counterChanged(int);
public slots:
    void sliderChange(int counter);
};

#endif // WIDGET_H
