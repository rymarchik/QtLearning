#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class GroupBox : public QGroupBox
{
    Q_OBJECT

public:
    GroupBox(QWidget *parent = 0);

private:
    QRadioButton* r1;
    QRadioButton* r2;
    QRadioButton* r3;
    QCheckBox* c1;

public slots:
    void buttonClicked();
//    void funny(QPushButton* b);
//    void sad(QPushButton* b);
};

#endif // MAINWINDOW_H
