#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtWidgets>
#include <QStack>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget* wgt = 0);
    QPushButton* createButton(const QString& str);
    void calculate();

private:
    QLCDNumber* lcd;
    QStack<QString> stack;
    QString display;

public slots:
    void slotButtonClicked();
};

#endif // CALCULATOR_H
