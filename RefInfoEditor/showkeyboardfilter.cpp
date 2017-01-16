#include "showkeyboardfilter.h"

ShowKeyboardFilter::ShowKeyboardFilter(QObject *parent) : QObject(parent)
{
}

bool ShowKeyboardFilter::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::FocusIn) {
        openKeyboard();
    }
    else if (event->type() == QEvent::FocusOut) {
        closeKeyboard();
    }
    return false;
}
QString ShowKeyboardFilter::copyToQString(WCHAR array[MAX_PATH]) {
    QString string;
    int i = 0;
    while (array[i] != 0)
    {
        string[i] = array[i];
        i++;
    }
    return string;
}

void ShowKeyboardFilter::openKeyboard() {
    process->execute(virtualKeyboard);
}
// globalPos = widget->mapToGlobal(QPoint(0, widget->height()));
// QWidget::move(globalX, globalY);

void ShowKeyboardFilter::closeKeyboard() {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 proc = { sizeof(proc) };
    if (Process32First(hSnap, &proc))
    {
        while (Process32Next(hSnap, &proc))
        {
            QString fileName = copyToQString(proc.szExeFile);
            if(fileName == QString("osk.exe"))
            {
                HANDLE hp = OpenProcess(1, false, proc.th32ProcessID );
                TerminateProcess(hp, 0);
            }
        }
    }
}
