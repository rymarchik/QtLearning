#include "editor.h"
#include "dialog.h"

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    dialog(new Dialog(this))
{
    resize(915, 580);

    tools = addToolBar("Панель инструментов");
    tools->setMovable(false);
    tools->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tools->setIconSize(QSize(40,40));

    addAction = new QAction(QIcon(":/resources/add.png"), "Добавить");
    editAction = new QAction(QIcon(":/resources/edit.png"), "Изменить");
    deleteAction = new QAction(QIcon(":/resources/delete.png"), "Удалить");
    searchAction = new QAction(QIcon(":/resources/search.png"), "Поиск");
    uploadAction = new QAction(QIcon(":/resources/upload.png"), "Сохранить");
    downloadAction = new QAction(QIcon(":/resources/download.png"), "Загрузить");
    exitAction = new QAction(QIcon(":/resources/exit.png"), "Выход");
    tools->addAction(addAction);
    tools->addAction(editAction);
    tools->addAction(deleteAction);
    tools->addAction(searchAction);
    tools->addSeparator();
    tools->addAction(uploadAction);
    tools->addAction(downloadAction);
    tools->addSeparator();
    tools->addAction(exitAction);

    directory = new QListWidget;
    directory->setMaximumWidth(this->width()/4);

    hiddenDataTable = new QTableWidget;
    hiddenDataTable->setHidden(true);
    hiddenDataTable->setMaximumHeight(this->height()/4);
    hiddenDataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    hiddenDataTable->horizontalHeader()->setFrameShape(QFrame::StyledPanel);
    hiddenDataTable->horizontalHeader()->setFrameShadow(QFrame::Raised);
    hiddenDataTable->verticalHeader()->setVisible(false);
    hiddenDataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    hiddenDataTable->setShowGrid(false);

    dataTable = new QTableWidget;
    header = dataTable->horizontalHeader();
    header->setFrameShape(QFrame::StyledPanel);
    header->setFrameShadow(QFrame::Raised);
    dataTable->verticalHeader()->setVisible(false);
    dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    dataTable->setShowGrid(false);


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

    connect(directory, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotShowDirectoryInfo(QListWidgetItem*)));

    setCentralWidget(window);
    setWindowIcon(QIcon(":/resources/title.png"));
    setWindowTitle("Редактор нормативно-справочной информации");

    connect(addAction, SIGNAL(triggered()), this, SLOT(slotAdd()));
    connect(editAction, SIGNAL(triggered()), this, SLOT(slotEdit()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Editor::slotShowDirectoryInfo(QListWidgetItem* dirItem) {
    if (dirItem == directory->item(0)) {
        hiddenDataTable->setHidden(true);

        dataTable->clear();
        dataTable->setColumnCount(4);
        dataTable->setRowCount(3);

        QStringList headerNames;
        headerNames << "Тип БЧ ракеты" << "Радиус поражения, м" << "СКО по дальности, м" << "СКО боковое, м";
        dataTable->setHorizontalHeaderLabels(headerNames);

        dataTable->setItem(0,0,new QTableWidgetItem("A200-11"));
        dataTable->setItem(1,0,new QTableWidgetItem("A200-12"));
        dataTable->setItem(2,0,new QTableWidgetItem("A200-13"));
        dataTable->setItem(0,1,new QTableWidgetItem("80"));
        dataTable->setItem(1,1,new QTableWidgetItem("60"));
        dataTable->setItem(2,1,new QTableWidgetItem("30"));
        dataTable->setItem(0,2,new QTableWidgetItem("30"));
        dataTable->setItem(1,2,new QTableWidgetItem("30"));
        dataTable->setItem(2,2,new QTableWidgetItem("45"));
        dataTable->setItem(0,3,new QTableWidgetItem("30"));
        dataTable->setItem(1,3,new QTableWidgetItem("30"));
        dataTable->setItem(2,3,new QTableWidgetItem("45"));

        header->setSectionResizeMode(QHeaderView::Stretch);
//        header->setSectionResizeMode(header->logicalIndex(0), QHeaderView::ResizeToContents);
    }
    else if (dirItem == directory->item(1)) {
        hiddenDataTable->setHidden(true);

        dataTable->clear();
        dataTable->setColumnCount(2);
        dataTable->setRowCount(10);

        QStringList headerNames;
        headerNames << "Наименование степени поражения" << "Значение степени поражения";
        dataTable->setHorizontalHeaderLabels(headerNames);

        dataTable->setItem(2,0,new QTableWidgetItem("qwerty123456qwerty1234 56qwert"));

        header->setSectionResizeMode(QHeaderView::Stretch);
    }
    else if (dirItem == directory->item(2)) {
        hiddenDataTable->setHidden(true);

        dataTable->clear();
        dataTable->setColumnCount(4);
        dataTable->setRowCount(10);

        QStringList headerNames;
        headerNames << "Наименование объекта поражения" << "Наименование степени поражения"
                    << "Тип БЧ ракеты" << "Количество";
        dataTable->setHorizontalHeaderLabels(headerNames);

        dataTable->setItem(0,0,new QTableWidgetItem("qwerty123456qwerty1234fffffffffffffffffffgsgsgsgsg"));

        header->setSectionResizeMode(QHeaderView::Stretch);
    }
    else if (dirItem == directory->item(3)) {
        hiddenDataTable->setHidden(true);

        dataTable->clear();
        dataTable->setColumnCount(3);
        dataTable->setRowCount(10);

        QStringList headerNames;
        headerNames << "Наименование цели" << "Фронт, м" << "Глубина, м";
        dataTable->setHorizontalHeaderLabels(headerNames);

        dataTable->setItem(0,0,new QTableWidgetItem("qwerty123456qwerty1234 56qwerty123456"));


        header->setSectionResizeMode(QHeaderView::Stretch);
    }
    else if (dirItem == directory->item(4)) {
        hiddenDataTable->setHidden(false);
        hiddenDataTable->setColumnCount(1);
        hiddenDataTable->setRowCount(5);
        hiddenDataTable->setHorizontalHeaderLabels(QStringList("Высота БМ, м"));

        hiddenDataTable->setItem(0,0,new QTableWidgetItem("1000"));


        dataTable->clear();
        dataTable->setColumnCount(9);
        dataTable->setRowCount(10);

        QStringList headerNames;
        headerNames << "Дальность до цели, км" << "Угол пуска, град" << "Время полета, с"
                    << "Максимальная высота\n траектории, м" << "Место падения двигателя\n по умолчанию, м"
                    << "Минимальное расстояние места\n падения двигателя, м"
                    << "Максимальное расстояние места\n падения двигателя, м"
                    << "Минимальное время\n разделения, с" << "Максимальное время\n разделения, с";
        dataTable->setHorizontalHeaderLabels(headerNames);

        dataTable->setItem(0,0,new QTableWidgetItem("qwerty123456 7890090909"));


        header->setSectionResizeMode(QHeaderView::Stretch);
        header->setSectionResizeMode(header->logicalIndex(0), QHeaderView::ResizeToContents);
//        header->setSectionResizeMode(header->logicalIndex(1), QHeaderView::ResizeToContents);
//        header->setSectionResizeMode(header->logicalIndex(2), QHeaderView::ResizeToContents);
        header->setSectionResizeMode(header->logicalIndex(3), QHeaderView::ResizeToContents);
        header->setSectionResizeMode(header->logicalIndex(4), QHeaderView::ResizeToContents);
        header->setSectionResizeMode(header->logicalIndex(5), QHeaderView::ResizeToContents);
        header->setSectionResizeMode(header->logicalIndex(6), QHeaderView::ResizeToContents);
        header->setSectionResizeMode(header->logicalIndex(7), QHeaderView::ResizeToContents);
        header->setSectionResizeMode(header->logicalIndex(8), QHeaderView::ResizeToContents);

        qDebug() << header->logicalIndex(0) << header->logicalIndex(1) << header->logicalIndex(2)
                 << header->logicalIndex(3) << header->logicalIndex(4);
    }
}

void Editor::slotChangeRootItemValue(int n) {
    if (n != -1) {
        QStringList list;
        for (int i = 0; i < dataTable->columnCount() - 1; i++) {
            list.append(dataTable->item(n, i + 1)->text());
        }
        dialog->setItemValues(list);
        dialog->setLineEdits(list.size());
    }
}

void Editor::slotAdd() {
    dialog->setWindowTitle(directory->currentItem()->text());

    dialog->setHeaderNames(getHeaderNames());
    dialog->setEmptyLineEdits(getHeaderNames().size());

    if (dialog->exec() == QDialog::Accepted) {
        qDebug() << "add";
    }
}

void Editor::slotEdit() {
    dialog->setWindowTitle(directory->currentItem()->text());

    dialog->setHeaderNames(getHeaderNames());
    dialog->setRootItemValues(getRootItemValues());

    if (dialog->exec() == QDialog::Accepted) {
        qDebug() << "edit";
    }
//    QModelIndex curentIndex = table->currentIndex();

//    qDebug() << table->item(curentIndex.row(), 0)->text();
//    qDebug() << table->item(curentIndex.row(), 1)->text();
}

QStringList Editor::getHeaderNames() {
    QStringList list;
    for (int i = 0; i < dataTable->columnCount(); i++) {
        list.append(dataTable->horizontalHeaderItem(i)->text());
    }
    return list;
}

QStringList Editor::getRootItemValues() {
    QStringList list;
    for (int i = 0; i < dataTable->rowCount(); i++) {
        list.append(dataTable->item(i, 0)->text());
    }
    return list;
}
