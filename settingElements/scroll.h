#ifndef SCROLL_H
#define SCROLL_H
#include <QtWidgets>

class Scroll: public QWidget {
    Q_OBJECT
public:
    Scroll();
private:
    QLCDNumber* lcd;
    QScrollBar* scr;
};

#endif // SCROLL_H
