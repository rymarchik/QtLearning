#include "dlgdialog.h"
#include "ui_dlgdialog.h"
#include <QtGui>

dlgDialog::dlgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgDialog)
{
    ui->setupUi(this);
    ui->labelTermname->setBuddy(ui->lineEditTermname);
    ui->lineEditTermname->setFocus();


}

void  dlgDialog::setTextLineEdit(QString Termname, QString Termhierarchy, QString Termshortname)
{
    ui->lineEditTermname->setText(Termname);
    ui->lineEditTermhierarchy->setText(Termhierarchy);
    ui->lineEditTermshortname->setText(Termshortname);
}

QString dlgDialog::getLineEditTermname()
{
    return ui->lineEditTermname->text();
}

QString dlgDialog::getLineEditTermhierarchy()
{
    return ui->lineEditTermhierarchy->text();
}

QString dlgDialog::getLineEditTermshortname()
{
    return ui->lineEditTermshortname->text();
}

void dlgDialog::startProcess()
{
    process->start(program);
}

void dlgDialog::killProcess()
{
    //qDebug() << "From killProcess(): m_process_id = " << m_process_id;
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

QString dlgDialog::copyToQString(WCHAR array[MAX_PATH])
{
    QString string;
    int i = 0;
    while (array[i] != 0)
    {
        string[i] = array[i];
        i++;
    }
    return string;
}

dlgDialog::~dlgDialog()
{
    delete ui;
}


