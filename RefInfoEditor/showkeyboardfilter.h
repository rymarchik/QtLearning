#ifndef SHOWKEYBOARDFILTER_H
#define SHOWKEYBOARDFILTER_H

#include <QtWidgets>
#include <QProcess>
#include <windows.h>
#include <tlhelp32.h>
#include "ShellAPI.h"

class ShowKeyboardFilter : public QObject
{
    Q_OBJECT

public:
    explicit ShowKeyboardFilter(QObject *parent = 0);

    void openKeyboard();
    void closeKeyboard();

    QString copyToQString(WCHAR array[MAX_PATH]);

private:
    QProcess* process = new QProcess(this);
    QString virtualKeyboard = "explorer.exe C:\\Windows\\System32\\osk.exe";

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

public slots:
};

#endif // SHOWKEYBOARDFILTER_H
