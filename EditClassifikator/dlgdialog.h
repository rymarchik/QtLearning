#ifndef DLGDIALOG_H
#define DLGDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QProcess>
#include <QDebug>
#include <QString>
#include <windows.h>
#include <tlhelp32.h>
#include "ShellAPI.h"

namespace Ui {
class dlgDialog;
}

class dlgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit dlgDialog(QWidget *parent = 0);
    ~dlgDialog();
    QString m_textTermname;
    QString m_textTermhierarchy;
    QString m_textTermshortname;

    bool m_Accepted = false;

    QProcess *process = new QProcess(this);
    QString   program = "explorer.exe C:\\Windows\\System32\\osk.exe";


public:
    void startProcess();
    void killProcess();
    void setTextLineEdit(QString Termname, QString Termhierarchy, QString Termshortname);

    QString getLineEditTermname();
    QString getLineEditTermhierarchy();
    QString getLineEditTermshortname();

    QString copyToQString(WCHAR array[MAX_PATH]);

private:
    Ui::dlgDialog *ui;    


};

#endif // DLGDIALOG_H
