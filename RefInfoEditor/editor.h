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

    QStringList getToBeAddedColumnValues();
    QStringList getToBeEditedColumnValues();
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
    void slotActivateEditDeleteButton();

    void slotAddDialChangeComboBox1(int);
    void slotAddDialChangeComboBox2(int);
    void slotEditDialChangeComboBox1(int);
    void slotEditDialChangeComboBox2(int);
    void slotEditDialChangeComboBox3(int);

    void slotAdd();
    void slotEdit();
    void slotDelete();
};

#endif // EDITOR_H
