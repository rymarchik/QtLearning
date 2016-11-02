#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QtWidgets>

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);

private:
    QToolBar* tools;
    QAction* addAction;
    QAction* editAction;
    QAction* deleteAction;
    QAction* saveAction;
    QAction* searchAction;
    QAction* refreshAction;
    QAction* exitAction;

    QWidget* window;
    QListWidget* directory;
    QTableWidget* dataTable;
    QTableWidget* hiddenDataTable;
};

#endif // EDITOR_H
