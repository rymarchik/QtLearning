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

    QStringList getHeaderNames();
    QStringList getRootItemValues();

private:
    QToolBar* tools;
    QAction* addAction;
    QAction* editAction;
    QAction* deleteAction;
    QAction* searchAction;
    QAction* uploadAction;
    QAction* downloadAction;
    QAction* exitAction;

    QWidget* window;
    QListWidget* directory;
    QTableWidget* hiddenDataTable;
    QTableWidget* dataTable;
    QHeaderView* header;

    Dialog* dialog;
    QSqlDatabase db;

private slots:
    void slotShowDirectoryInfo(QListWidgetItem*);
    void slotChangeRootItemValue(int);
    void slotAdd();
    void slotEdit();
};

#endif // EDITOR_H
