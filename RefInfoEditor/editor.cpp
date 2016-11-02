#include "editor.h"

Editor::Editor(QWidget *parent) :
    QMainWindow(parent)
{
    resize(915, 580);

    tools = addToolBar("Панель инструментов");
    tools->setMovable(false);
    tools->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tools->setIconSize(QSize(40,40));

    addAction = new QAction(QIcon(":/resources/add.png"), "Добавить");
    editAction = new QAction(QIcon(":/resources/edit.png"), "Изменить");
    deleteAction = new QAction(QIcon(":/resources/delete.png"), "Удалить");
    saveAction = new QAction(QIcon(":/resources/save.png"), "Сохранить");
    searchAction = new QAction(QIcon(":/resources/search.png"), "Поиск");
    refreshAction = new QAction(QIcon(":/resources/refresh.png"), "Обновить");
    exitAction = new QAction(QIcon(":/resources/exit.png"), "Выход");
    tools->addAction(addAction);
    tools->addAction(editAction);
    tools->addAction(deleteAction);
    tools->addAction(saveAction);
    tools->addAction(searchAction);
    tools->addAction(refreshAction);
    tools->addSeparator();
    tools->addAction(exitAction);

    directory = new QListWidget;
    directory->setMaximumWidth(this->width()/4);

    hiddenDataTable = new QTableWidget;
//    hiddenDataTable->setHidden(true);
    hiddenDataTable->setMaximumHeight(this->height()/4);
    dataTable = new QTableWidget;
    QVBoxLayout* dataLayout = new QVBoxLayout;
    dataLayout->addWidget(hiddenDataTable);
    dataLayout->addWidget(dataTable);

    QHBoxLayout* centralLayout = new QHBoxLayout;
    centralLayout->addWidget(directory);
    centralLayout->addLayout(dataLayout);

    window = new QWidget;
    window->setLayout(centralLayout);

    setStatusBar(new QStatusBar);

    QStringList dirList;
    dirList << "Характеристики БЧ" << "Степень поражения" << "Нормативы поражения целей"
            << "Типовые размеры площадных целей" << "Таблица стрельбы";
    QListWidgetItem* dirItem = 0;
    foreach (QString str, dirList) {
        dirItem = new QListWidgetItem(str, directory);
        dirItem->setTextAlignment(Qt::AlignCenter);
    }




    setCentralWidget(window);
    setWindowIcon(QIcon(":/resources/title.png"));
    setWindowTitle("Редактор нормативно-справочной информации");

    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}
