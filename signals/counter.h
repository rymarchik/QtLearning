#pragma once
#include <QObject>

class Counter : public QObject
{
    Q_OBJECT

private:
    int m_nValue;
public:
    Counter();
public slots:
    void slotInc(const QString&);

signals:
    void goodbye();
    void counterChanged(int);
};
