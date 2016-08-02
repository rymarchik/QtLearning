#include "calculator.h"

Calculator::Calculator(QWidget *wgt) : QWidget(wgt) {
    lcd = new QLCDNumber(12);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setMinimumSize(150,50);

    QChar aButtons[4][4] = {{'7','8','9','/'},
                            {'4','5','6','*'},
                            {'1','2','3','-'},
                            {'0','.','=','+'}
                           };

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(lcd, 0, 0, 1, 4);
    layout->addWidget(createButton("CE"), 1, 3);

    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            layout->addWidget(createButton(aButtons[i][j]), i+2, j);
        }
    }
    setLayout(layout);
}

QPushButton* Calculator::createButton(const QString& str) {
    QPushButton* button = new QPushButton(str);
    button->setMinimumSize(40, 40);
    connect(button, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return button;
}

void Calculator::calculate() {
    double oper2 = stack.pop().toDouble();
    QString sign = stack.pop();
    double oper1 = stack.pop().toDouble();
    double result = 0;

    if (sign == "/") {
        result = oper1 / oper2;
    }
    if (sign == "*") {
        result = oper1 * oper2;
    }
    if (sign == "+") {
        result = oper1 + oper2;
    }
    if (sign == "-") {
        result = oper1 - oper2;
    }

    lcd->display(result);
}

void Calculator::slotButtonClicked() {
    QString str = ((QPushButton*)sender())->text();

    if (str == "CE") {
        stack.clear();
        display = "";
        lcd->display("0");
        return;
    }
    if (str.contains(QRegExp("[0-9]"))) {
        display += str;
        lcd->display(display.toDouble());
    }
    else if (str == ".") {
        display += str;
        lcd->display(display);
    }
    else {
        if (stack.count() == 0 and str != "="){
            stack.push(QString().setNum(lcd->value()));
            stack.push(str);
            display = "";
        }

        else if (stack.count() == 2 && display.contains(QRegExp("[0-9]"))) {
            stack.push(QString().setNum(lcd->value()));
            calculate();
            stack.clear();
            if (str != "=") {
                stack.push(QString().setNum(lcd->value()));
                stack.push(str);
            }
            display = "";
        }

        else if (str != "=") {
            stack.pop();
            stack.push(str);
        }
    }
}
