#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>

class Dialog;

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);

    QStringList getLowerTableHeaderNames();
    QStringList getAllTableHeaderNames();
    QStringList getRootColumnValues();
    QStringList getUpperTableColumnValues();

private:
    QToolBar* tools;
    QAction* addAction;
    QAction* editAction;
    QAction* deleteAction;
    QAction* searchAction;
    QAction* uploadAction;
    QAction* downloadAction;
    QAction* exitAction;

    QWidget* contentWindow;
    QListWidget* directoryList;
    QTableWidget* upperTable;
    QTableWidget* lowerTable;
    QHeaderView* lowerTableHeader;

    Dialog* dialog;
    QSqlDatabase db;

private slots:
    void slotShowDirectoryInfo(QListWidgetItem*);
    void slotShowLowerFireTable();
    void slotActivateDeleteButton();

    void slotChangeRootItemValue(int);
    void slotChange2ndRootItemValue(int);
    void slotChange3rdRootItemValue(int);

    void slotAdd();
    void slotEdit();
    void slotDelete();
};

#endif // EDITOR_H
