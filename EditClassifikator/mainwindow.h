#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QProcess>
#include <QVariant>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class dlgDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSqlQuery sql, query;
    QMessageBox message;  
    QString m_textTermname;
    QString m_textTermhierarchy;
    QString m_textTermshortname;

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    int numDialog = 0;

private slots:
    void slotAdd();
    void slotEdit();
    void slotDelete();
    void slotSave();
    void showDialog();
    void slotFind();
    void slotRefresh();
    void slotGetParam();
    void slotDlgRejected();
    void slotDlgAccepted();

private:
    dlgDialog *m_dlgDialog;
};

#endif // MAINWINDOW_H
