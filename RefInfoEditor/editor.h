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
    QAction* searchAction;
    QAction* uploadAction;
    QAction* downloadAction;
    QAction* exitAction;

    QWidget* window;
    QListWidget* directory;
    QTableWidget* hiddenDataTable;
    QTableWidget* dataTable;
    QHeaderView* header;

private slots:
    void showDirectoryInfo(QListWidgetItem* item);
};

#endif // EDITOR_H
