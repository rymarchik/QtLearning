#include "counter.h"
#include "QSignalMapper"
#include "QPushButton"

Counter::Counter() : QObject()
   , m_nValue(0)
{

}

void Counter::slotInc(const QString&) {
    emit counterChanged(++m_nValue);

    if (m_nValue == 5) {
        emit goodbye();
    }
}
