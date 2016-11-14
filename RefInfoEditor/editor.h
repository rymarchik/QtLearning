#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QtWidgets>

class Dialog;

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);

    QStringList getHeaderNames();
    QStringList getRootItemValues();
    QStringList getItemValues();

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

private slots:
    void showDirectoryInfo(QListWidgetItem* item);
    void slotAdd();
    void slotEdit();
};

#endif // EDITOR_H
