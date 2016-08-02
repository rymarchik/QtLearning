#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

class Progress : public QWidget
{
    Q_OBJECT

private:
    QProgressBar* bar;
    int step;
public:
    Progress(QWidget *parent = 0);
public slots:
    void slotStep();
    void slotReset();
};

#endif // WIDGET_H
