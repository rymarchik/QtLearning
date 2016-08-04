#ifndef DIAL_H
#define DIAL_H
#include <QtWidgets>

class Dial: public QWidget {
    Q_OBJECT
public:
    Dial();
private:
    QDial* dial;
    QProgressBar* prb;
};

#endif // DIAL_H
