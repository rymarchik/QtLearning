#include "calculator.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator calc;

    calc.setGeometry(555,222,230,200);
    calc.setWindowTitle("Calculator");

    calc.show();

    return a.exec();
}
