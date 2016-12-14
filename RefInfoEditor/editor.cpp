#include "editor.h"
#include "dialog.h"

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    dialog(new Dialog(this))
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("A200");
    db.setUserName("asrymarchik");
    db.setPassword("123456");
    db.setHostName("192.168.1.42");
    db.setPort(5432);
//    db.setDatabaseName("postgres");
//    db.setUserName("postgres");
//    db.setPassword("root");
//    db.setHostName("localhost");
//    db.setPort(5432);

    if (!db.open()) {
        qDebug() << "Can't open database: " << db.lastError();
    }

    resize(1000, 580);

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

    addAction->setEnabled(false);
    editAction->setEnabled(false);
    deleteAction->setEnabled(false);

    tools->addAction(addAction);
    tools->addAction(editAction);
    tools->addAction(deleteAction);
    tools->addAction(searchAction);
    tools->addSeparator();
    tools->addAction(uploadAction);
    tools->addAction(downloadAction);
    tools->addSeparator();
    tools->addAction(exitAction);

    directoryList = new QListWidget;
    directoryList->setMaximumWidth(this->width()/4);

    upperTable = new QTableWidget;
    upperTable->setHidden(true);
    upperTable->setMaximumHeight(this->height()/4);
    upperTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    upperTable->horizontalHeader()->setFrameShape(QFrame::StyledPanel);
    upperTable->horizontalHeader()->setFrameShadow(QFrame::Raised);
    upperTable->verticalHeader()->setVisible(false);
    upperTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    upperTable->setShowGrid(false);

    lowerTable = new QTableWidget;
    lowerTableHeader = lowerTable->horizontalHeader();
    lowerTableHeader->setFrameShape(QFrame::StyledPanel);
    lowerTableHeader->setFrameShadow(QFrame::Raised);
    lowerTable->verticalHeader()->setVisible(false);
    lowerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    lowerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    lowerTable->setShowGrid(false);


    QVBoxLayout* dataLayout = new QVBoxLayout;
    dataLayout->addWidget(upperTable);
    dataLayout->addWidget(lowerTable);

    QHBoxLayout* centralLayout = new QHBoxLayout;
    centralLayout->addWidget(directoryList);
    centralLayout->addLayout(dataLayout);

    contentWindow = new QWidget;
    contentWindow->setLayout(centralLayout);

    setStatusBar(new QStatusBar);

    QStringList dirList;
    dirList << "Характеристики БЧ" << "Степень поражения" << "Нормативы поражения целей"
            << "Типовые размеры площадных целей" << "Таблица стрельбы";
    QListWidgetItem* dirItem = 0;
    foreach (QString str, dirList) {
        dirItem = new QListWidgetItem(str, directoryList);
        dirItem->setTextAlignment(Qt::AlignCenter);
    }

    connect(directoryList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotShowDirectoryInfo(QListWidgetItem*)));
    connect(upperTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotShowLowerFireTable()));
    connect(upperTable, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(slotActivateEditDeleteButton()));
    connect(lowerTable, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(slotActivateEditDeleteButton()));

    connect(addAction, SIGNAL(triggered()), this, SLOT(slotAdd()));
    connect(editAction, SIGNAL(triggered()), this, SLOT(slotEdit()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(slotDelete()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    setCentralWidget(contentWindow);
    setWindowIcon(QIcon(":/resources/title.png"));
    setWindowTitle("Редактор нормативно-справочной информации");
}

void Editor::slotActivateEditDeleteButton() {
    editAction->setEnabled(true);
    deleteAction->setEnabled(true);
}

void Editor::slotShowDirectoryInfo(QListWidgetItem* dirItem) {
    addAction->setEnabled(true);
    editAction->setEnabled(false);
    deleteAction->setEnabled(false);

    if (dirItem == directoryList->item(0)) {
        upperTable->setHidden(true);
        lowerTableHeader->setHidden(false);
        lowerTable->clear();

        QSqlQuery query;
        QString selectQuery = "SELECT t.termname, w.attack_range, w.deviation_range, w.deviation_lateral FROM "
                             "reference_data.terms t JOIN target_distribution.warhead_characteristics w ON "
                             "t.termhierarchy = w.rocket_type";
        if (!query.exec(selectQuery)) {
            qDebug() << "Unable to make select operation";
        }

        QSqlRecord rec = query.record();

        lowerTable->setColumnCount(rec.count());
        lowerTable->setRowCount(query.size());

        int i = 0;
        while(query.next()) {
            lowerTable->setItem(i, 0, new QTableWidgetItem(query.value(rec.indexOf("termname")).toString()));
            lowerTable->setItem(i, 1, new QTableWidgetItem
                               (tr("%1").arg(query.value(rec.indexOf("attack_range")).toInt())));
            lowerTable->setItem(i, 2, new QTableWidgetItem
                               (tr("%1").arg(query.value(rec.indexOf("deviation_range")).toInt())));
            lowerTable->setItem(i, 3, new QTableWidgetItem
                               (tr("%1").arg(query.value(rec.indexOf("deviation_lateral")).toInt())));
            i++;
        }

        QStringList headerNames;
        headerNames << "Тип БЧ ракеты" << "Радиус поражения, м" << "СКО по дальности, м" << "СКО боковое, м";
        lowerTable->setHorizontalHeaderLabels(headerNames);

        lowerTableHeader->setSectionResizeMode(QHeaderView::Stretch);
    }
    else if (dirItem == directoryList->item(1)) {
        upperTable->setHidden(true);
        lowerTableHeader->setHidden(false);
        lowerTable->clear();

        QSqlQuery query;
        QString selectQuery = "SELECT t.termname, d.value FROM reference_data.terms t JOIN "
                             "target_distribution.damage_degree d ON "
                             "t.termhierarchy = d.degree_name";
        if (!query.exec(selectQuery)) {
            qDebug() << "Unable to make select operation";
        }

        QSqlRecord rec = query.record();

        lowerTable->setColumnCount(rec.count());
        lowerTable->setRowCount(query.size());

        int i = 0;
        while(query.next()) {
            lowerTable->setItem(i, 0, new QTableWidgetItem(query.value(rec.indexOf("termname")).toString()));
            lowerTable->setItem(i, 1, new QTableWidgetItem
                               (tr("%1").arg(query.value(rec.indexOf("value")).toDouble())));
            i++;
        }

        QStringList headerNames;
        headerNames << "Наименование степени поражения" << "Значение степени поражения";
        lowerTable->setHorizontalHeaderLabels(headerNames);

        lowerTableHeader->setSectionResizeMode(QHeaderView::Stretch);
    }
    else if (dirItem == directoryList->item(2)) {
        upperTable->setHidden(true);
        lowerTableHeader->setHidden(false);
        lowerTable->clear();

        QSqlQuery query;
        QString selectQuery = "SELECT t1.termname, t2.termname, t3.termname, d.quantity FROM "
                              "target_distribution.damage_regulations d JOIN reference_data.terms t1 "
                              "ON d.obj_name = t1.termhierarchy JOIN reference_data.terms t2 "
                              "ON d.degree_name = t2.termhierarchy JOIN reference_data.terms t3 "
                              "ON d.rocket_type = t3.termhierarchy ORDER BY t1.termhierarchy";
        if (!query.exec(selectQuery)) {
            qDebug() << "Unable to make select operation";
        }

        lowerTable->setColumnCount(4);
        lowerTable->setRowCount(query.size());

        int i = 0;
        while(query.next()) {
            lowerTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
            lowerTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
            lowerTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString()));
            lowerTable->setItem(i, 3, new QTableWidgetItem(tr("%1").arg(query.value(3).toInt())));
            i++;
        }

        QStringList headerNames;
        headerNames << "Наименование объекта поражения" << "Наименование степени поражения"
                    << "Тип БЧ ракеты" << "Количество";
        lowerTable->setHorizontalHeaderLabels(headerNames);

        lowerTableHeader->setSectionResizeMode(QHeaderView::Stretch);
        lowerTableHeader->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        lowerTableHeader->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        lowerTableHeader->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    }
    else if (dirItem == directoryList->item(3)) {
        upperTable->setHidden(true);
        lowerTableHeader->setHidden(false);
        lowerTable->clear();

        QSqlQuery query;
        QString selectQuery = "SELECT t.termname, ts.front, ts.depth FROM reference_data.terms t JOIN "
                             "target_distribution.target_size ts ON t.termhierarchy = ts.target_name";
        if (!query.exec(selectQuery)) {
            qDebug() << "Unable to make select operation";
        }

        QSqlRecord rec = query.record();

        lowerTable->setColumnCount(rec.count());
        lowerTable->setRowCount(query.size());

        int i = 0;
        while(query.next()) {
            lowerTable->setItem(i, 0, new QTableWidgetItem(query.value(rec.indexOf("termname")).toString()));
            lowerTable->setItem(i, 1, new QTableWidgetItem
                               (tr("%1").arg(query.value(rec.indexOf("front")).toInt())));
            lowerTable->setItem(i, 2, new QTableWidgetItem
                               (tr("%1").arg(query.value(rec.indexOf("depth")).toInt())));
            i++;
        }

        QStringList headerNames;
        headerNames << "Наименование цели" << "Фронт, м" << "Глубина, м";
        lowerTable->setHorizontalHeaderLabels(headerNames);

        lowerTableHeader->setSectionResizeMode(QHeaderView::Stretch);
    }
    else if (dirItem == directoryList->item(4)) {
        upperTable->setHidden(false);
        upperTable->clear();
        lowerTableHeader->setHidden(true);
        lowerTable->clear();


        QSqlQuery query;
        QString selectUpperTableQuery = "SELECT DISTINCT obj_height FROM target_distribution.fire_table ORDER BY obj_height";

        if (!query.exec(selectUpperTableQuery)) {
            qDebug() << "Unable to make select operation";
        }

        QSqlRecord rec = query.record();

        upperTable->setColumnCount(1);
        upperTable->setRowCount(query.size());

        int i = 0;
        while(query.next()) {
            upperTable->setItem(i, 0, new QTableWidgetItem
                                     (tr("%1").arg(query.value(rec.indexOf("obj_height")).toInt())));
            i++;
        }

        upperTable->setHorizontalHeaderLabels(QStringList("Высота БМ, м"));
    }
}

void Editor::slotShowLowerFireTable() {
    lowerTableHeader->setHidden(false);
    lowerTable->clear();

    QSqlQuery query;
    QString selectLowerTablePattern = "SELECT target_distance, launch_angle, flight_time, trajectory_maxheight, "
                          "engine_drop_default, engine_drop_min, engine_drop_max, separation_time_min, "
                          "separation_time_max FROM target_distribution.fire_table "
                          "WHERE obj_height = %1 ORDER BY target_distance";
    QString selectQuery = selectLowerTablePattern.arg(upperTable->currentItem()->text());

    if (!query.exec(selectQuery)) {
        qDebug() << "Unable to make select operation";
    }

    QSqlRecord rec = query.record();

    lowerTable->setColumnCount(rec.count());
    lowerTable->setRowCount(query.size());

    int i = 0;
    while(query.next()) {
        lowerTable->setItem(i, 0, new QTableWidgetItem
                           (tr("%1").arg(query.value(rec.indexOf("target_distance")).toInt())));
        lowerTable->setItem(i, 1, new QTableWidgetItem
                           (tr("%1").arg(query.value(rec.indexOf("launch_angle")).toDouble())));
        lowerTable->setItem(i, 2, new QTableWidgetItem
                           (tr("%1").arg(query.value(rec.indexOf("flight_time")).toDouble())));
        lowerTable->setItem(i, 3, new QTableWidgetItem
                           (tr("%1").arg(query.value(rec.indexOf("trajectory_maxheight")).toDouble())));
        lowerTable->setItem(i, 4, new QTableWidgetItem
                           (tr("%1").arg(query.value(rec.indexOf("engine_drop_default")).toInt())));
        lowerTable->setItem(i, 5, new QTableWidgetItem
                           (tr("%1").arg(query.value(rec.indexOf("engine_drop_min")).toInt())));
        lowerTable->setItem(i, 6, new QTableWidgetItem
                           (tr("%1").arg(query.value(rec.indexOf("engine_drop_max")).toInt())));
        lowerTable->setItem(i, 7, new QTableWidgetItem
                           (tr("%1").arg(query.value(rec.indexOf("separation_time_min")).toDouble())));
        lowerTable->setItem(i, 8, new QTableWidgetItem
                           (tr("%1").arg(query.value(rec.indexOf("separation_time_max")).toDouble())));
        i++;
    }

    QStringList headerNames;
    headerNames << "Дальность до цели, км" << "Угол пуска, град" << "Время полета, с"
                << "Максимальная высота\nтраектории, м" << "Место падения двигателя\nпо умолчанию, м"
                << "Минимальное расстояние места\nпадения двигателя, м"
                << "Максимальное расстояние места\nпадения двигателя, м"
                << "Минимальное время\nразделения, с" << "Максимальное время\nразделения, с";
    lowerTable->setHorizontalHeaderLabels(headerNames);

    lowerTableHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void Editor::slotEditDialChangeComboBox1(int n) {
    if (n != -1) {
        if (directoryList->currentItem() == directoryList->item(2)) {
            if (lowerTable->hasFocus()) {
                dialog->setMainComboBoxCurrentText(lowerTable->item(lowerTable->currentRow(), 0)->text());
            }
            QStringList list;
            for (int i = 0; i < lowerTable->rowCount(); i++) {
                if (lowerTable->item(i, 0)->text() == dialog->getCurrentMainComboBoxText())
                    if (!list.contains(lowerTable->item(i, 1)->text()))
                        list.append(lowerTable->item(i, 1)->text());
            }
            qDebug() << list;
            dialog->setEditDialComboBox2Values(list);

//  ALSO WORKING OPTION -----------------------------------------------------------------------------------
//            QStringList list;
//            QSqlQuery query;
//            QString selectPattern = "SELECT DISTINCT t.termname FROM reference_data.terms t JOIN "
//                                    "target_distribution.damage_regulations dr ON "
//                                    "t.termhierarchy = dr.degree_name WHERE dr.obj_name IN "
//                                    "(SELECT dr.obj_name FROM target_distribution.damage_regulations dr "
//                                    "JOIN reference_data.terms t ON dr.obj_name = t.termhierarchy WHERE "
//                                    "t.termname = '%1')";
//            QString selectQuery = selectPattern.arg(dialog->getCurrentMainComboBoxText());
//            query.exec(selectQuery);
//            while(query.next()) {
//                list.append(query.value(0).toString());
//            }
//            qDebug() << list;
//            dialog->setSecondComboBoxValues(list);
        }
        else if (directoryList->currentItem() == directoryList->item(4)) {
            if (upperTable->hasFocus() || lowerTable->hasFocus()) {
                dialog->setMainComboBoxCurrentIndex(upperTable->currentRow());
            }
            else {
                upperTable->setCurrentItem(upperTable->item(n, 0));
            }
            QStringList list = getToBeEditedColumnValues();
            qDebug() << list;
            dialog->setEditDialComboBox2Values(list);
        }
        else {
            QStringList list;

            if (lowerTable->hasFocus()) {
                dialog->setMainComboBoxCurrentIndex(lowerTable->currentRow());
                for (int i = 0; i < lowerTable->columnCount() - 1; i++) {
                    list.append(lowerTable->item(lowerTable->currentRow(), i + 1)->text());
                }
            }
            else {
                for (int i = 0; i < lowerTable->columnCount() - 1; i++) {
                    list.append(lowerTable->item(n, i + 1)->text());
                }
            }
            dialog->fillFieldList(list);
            dialog->placeFieldList(list.size());

            QIntValidator* intValidator;
            QDoubleValidator* doubleValidator;
            QLocale locale(QLocale::C);
            locale.setNumberOptions(QLocale::RejectGroupSeparator);

            if (directoryList->currentItem() == directoryList->item(0)) {
                intValidator = new QIntValidator(10, 1000);
                dialog->setLineEditValidator(0, intValidator);
                dialog->setLineEditPlaceholder(0, "от 10 до 1000");

                intValidator = new QIntValidator(10, 999);
                dialog->setLineEditValidator(1, intValidator);
                dialog->setLineEditPlaceholder(1, "от 10 до 999");

                intValidator = new QIntValidator(10, 999);
                dialog->setLineEditValidator(2, intValidator);
                dialog->setLineEditPlaceholder(2, "от 10 до 999");
            }
            else if (directoryList->currentItem() == directoryList->item(1)) {
                doubleValidator = new QDoubleValidator(0.01, 1, 2);
                doubleValidator->setLocale(locale);
                doubleValidator->setNotation(QDoubleValidator::StandardNotation);
                dialog->setLineEditValidator(0, doubleValidator);
                dialog->setLineEditPlaceholder(0, "от 0.01 до 1");
            }
            else if (directoryList->currentItem() == directoryList->item(3)) {
                intValidator = new QIntValidator(10, 10000);
                dialog->setLineEditValidator(0, intValidator);
                dialog->setLineEditPlaceholder(0, "от 10 до 10000");

                intValidator = new QIntValidator(10, 10000);
                dialog->setLineEditValidator(1, intValidator);
                dialog->setLineEditPlaceholder(1, "от 10 до 10000");
            }
        }
    }
}

void Editor::slotEditDialChangeComboBox2(int n) {
    if (n != -1) {
        if (directoryList->currentItem() == directoryList->item(2)) {
            if (lowerTable->hasFocus()) {
                dialog->setSecondComboBoxCurrentText(lowerTable->item(lowerTable->currentRow(), 1)->text());
            }
            QStringList list;
            for (int i = 0; i < lowerTable->rowCount(); i++) {
                if (lowerTable->item(i, 0)->text() == dialog->getCurrentMainComboBoxText())
                   if (lowerTable->item(i, 1)->text() == dialog->getCurrentSecondComboBoxText())
                       list.append(lowerTable->item(i, 2)->text());
            }
            qDebug() << list;
            dialog->setEditDialComboBox3Values(list);
        }
        else if (directoryList->currentItem() == directoryList->item(4)) {
            QStringList list;

            if (lowerTable->hasFocus()) {
                dialog->setSecondComboBoxCurrentText(lowerTable->item(lowerTable->currentRow(), 0)->text());
                for (int i = 0; i < lowerTable->columnCount() - 1; i++) {
                    list.append(lowerTable->item(lowerTable->currentRow(), i + 1)->text());
                }
            }
            else {
                for (int i = 0; i < lowerTable->columnCount() - 1; i++) {
                    list.append(lowerTable->item(n, i + 1)->text());
                }
            }

            qDebug() << list;
            dialog->fillFieldList(list);
            dialog->placeFieldList(list.size());

            QIntValidator* intValidator;
            QDoubleValidator* doubleValidator;
            QLocale locale(QLocale::C);
            locale.setNumberOptions(QLocale::RejectGroupSeparator);

            doubleValidator = new QDoubleValidator(0, 89.999, 3);
            doubleValidator->setLocale(locale);
            doubleValidator->setNotation(QDoubleValidator::StandardNotation);
            dialog->setLineEditValidator(0, doubleValidator);
            dialog->setLineEditPlaceholder(0, "от 0.000 до 89.999");

            doubleValidator = new QDoubleValidator(9.999, 999.999, 3);
            doubleValidator->setLocale(locale);
            doubleValidator->setNotation(QDoubleValidator::StandardNotation);
            dialog->setLineEditValidator(1, doubleValidator);
            dialog->setLineEditPlaceholder(1, "от 9.999 до 999.999");

            intValidator = new QIntValidator(0, 8000);
            dialog->setLineEditValidator(2, intValidator);
            dialog->setLineEditPlaceholder(2, "от 0 до 8000");

            intValidator = new QIntValidator(1, 999999);
            dialog->setLineEditValidator(3, intValidator);
            dialog->setLineEditPlaceholder(3, "от 1 до 999999");

            intValidator = new QIntValidator(1, 999999);
            dialog->setLineEditValidator(4, intValidator);
            dialog->setLineEditPlaceholder(4, "от 1 до 999999");

            intValidator = new QIntValidator(1, 999999);
            dialog->setLineEditValidator(5, intValidator);
            dialog->setLineEditPlaceholder(5, "от 1 до 999999");

            doubleValidator = new QDoubleValidator(1, 99.999, 3);
            doubleValidator->setLocale(locale);
            doubleValidator->setNotation(QDoubleValidator::StandardNotation);
            dialog->setLineEditValidator(6, doubleValidator);
            dialog->setLineEditPlaceholder(6, "от 1 до 99.999");

            doubleValidator = new QDoubleValidator(1, 99.999, 3);
            doubleValidator->setLocale(locale);
            doubleValidator->setNotation(QDoubleValidator::StandardNotation);
            dialog->setLineEditValidator(7, doubleValidator);
            dialog->setLineEditPlaceholder(7, "от 1 до 99.999");
        }
    }
}

void Editor::slotEditDialChangeComboBox3(int n) {
    if (n != -1) {
        if (lowerTable->hasFocus()) {
            dialog->setThirdComboBoxCurrentText(lowerTable->item(lowerTable->currentRow(), 2)->text());
        }
        QStringList list;
        for (int i = 0; i < lowerTable->rowCount(); i++) {
            if (lowerTable->item(i, 0)->text() == dialog->getCurrentMainComboBoxText())
               if (lowerTable->item(i, 1)->text() == dialog->getCurrentSecondComboBoxText())
                   if (lowerTable->item(i, 2)->text() == dialog->getCurrentThirdComboBoxText())
                       list.append(lowerTable->item(i, 3)->text());
        }
        qDebug() << list;
        dialog->fillFieldList(list);
        dialog->placeFieldList(list.size());

        QIntValidator* intValidator = new QIntValidator(1, 99);
        dialog->setLineEditValidator(0, intValidator);
        dialog->setLineEditPlaceholder(0, "от 1 до 99");
    }
}

void Editor::slotAddDialChangeComboBox1(int n) {
    if (n != -1) {
        if (directoryList->currentItem() == directoryList->item(2)) {
            QSqlQuery query;
            QString selectPattern = "SELECT termname FROM reference_data.terms WHERE termhierarchy ~ '95.10.*' AND "
                                    "termhierarchy != '95.10'";
            query.exec(selectPattern);

            QStringList list;
            while (query.next()) {
                list.append(query.value(0).toString());
            }
            dialog->setAddDialComboBox2Values(list);
        }
        else if (directoryList->currentItem() == directoryList->item(4)) {
            if (upperTable->hasFocus() || lowerTable->hasFocus()) {
                dialog->setCurrentAddDialCB1Index(upperTable->currentRow());
            }
            else {
                upperTable->setCurrentItem(upperTable->item(n, 0));
            }
        }
    }
}

void Editor::slotAddDialChangeComboBox2(int n) {
    if (n != -1) {
        QSqlQuery query;
        QString selectCurrent = "SELECT t1.termhierarchy, t2.termhierarchy FROM reference_data.terms t1, reference_data.terms "
                                "t2 WHERE t1.termname = '%1' AND t2.termname = '%2'";
        QString selectCurrentQuery = selectCurrent.arg(dialog->getCurrentAddDialCB1Text()).arg(dialog->getCurrentAddDialCB2Text());
        query.exec(selectCurrentQuery);
        query.next();
        QString currentObject = query.value(0).toString();
        QString currentDegree = query.value(1).toString();

        QString selectPattern = "SELECT termname FROM reference_data.terms WHERE termhierarchy ~ '51.50.*' AND "
                                "termhierarchy != '51.50' AND termhierarchy NOT IN (SELECT rocket_type FROM "
                                "target_distribution.damage_regulations WHERE obj_name = '%1' AND degree_name = '%2')";
        QString selectQuery = selectPattern.arg(currentObject).arg(currentDegree);
        query.exec(selectQuery);

        QStringList list;
        while (query.next()) {
            list.append(query.value(0).toString());
        }
        qDebug() << list;
        dialog->setAddDialComboBox3Values(list);
    }
}

void Editor::slotAdd() {
    dialog->setWindowTitle(directoryList->currentItem()->text());
    dialog->openKeyboard();

    QIntValidator* intValidator;
    QDoubleValidator* doubleValidator;
    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    if (directoryList->currentItem() == directoryList->item(2)) {
        dialog->setLabelNames(getLowerTableHeaderNames());
        dialog->setEmptyLineEdits(1);
        dialog->setAddDialComboBox1Values(getToBeAddedColumnValues());

        intValidator = new QIntValidator(1, 99);
        dialog->setLineEditValidator(0, intValidator);
        dialog->setLineEditPlaceholder(0, "от 1 до 99");
    }
    else if (directoryList->currentItem() == directoryList->item(4)) {
        int i = 0;
        if (upperTable->hasFocus() || lowerTable->hasFocus()) {
            dialog->setLabelNames(getAllTableHeaderNames());
            dialog->setEmptyLineEdits(getLowerTableHeaderNames().size());
            dialog->setAddDialComboBox1Values(getUpperTableColumnValues());
        }
        else {
            upperTable->setCurrentItem(upperTable->item(0, 0));
            dialog->setLabelNames(getAllTableHeaderNames());
            dialog->setEmptyLineEdits(getAllTableHeaderNames().size());

            intValidator = new QIntValidator(0, 8000);
            dialog->setLineEditValidator(0, intValidator);
            dialog->setLineEditPlaceholder(0, "от 0 до 8000");
            i++;
        }

        intValidator = new QIntValidator(50, 200);
        dialog->setLineEditValidator(i, intValidator);
        dialog->setLineEditPlaceholder(i, "от 50 до 200 с шагом 10");

        doubleValidator = new QDoubleValidator(0, 89.999, 3);
        doubleValidator->setLocale(locale);
        doubleValidator->setNotation(QDoubleValidator::StandardNotation);
        dialog->setLineEditValidator(i + 1, doubleValidator);
        dialog->setLineEditPlaceholder(i + 1, "от 0.000 до 89.999");

        doubleValidator = new QDoubleValidator(9.999, 999.999, 3);
        doubleValidator->setLocale(locale);
        doubleValidator->setNotation(QDoubleValidator::StandardNotation);
        dialog->setLineEditValidator(i + 2, doubleValidator);
        dialog->setLineEditPlaceholder(i + 2, "от 9.999 до 999.999");

        intValidator = new QIntValidator(0, 8000);
        dialog->setLineEditValidator(i + 3, intValidator);
        dialog->setLineEditPlaceholder(i + 3, "от 0 до 8000");

        intValidator = new QIntValidator(1, 999999);
        dialog->setLineEditValidator(i + 4, intValidator);
        dialog->setLineEditPlaceholder(i + 4, "от 1 до 999999");

        intValidator = new QIntValidator(1, 999999);
        dialog->setLineEditValidator(i + 5, intValidator);
        dialog->setLineEditPlaceholder(i + 5, "от 1 до 999999");

        intValidator = new QIntValidator(1, 999999);
        dialog->setLineEditValidator(i + 6, intValidator);
        dialog->setLineEditPlaceholder(i + 6, "от 1 до 999999");

        doubleValidator = new QDoubleValidator(1, 99.999, 3);
        doubleValidator->setLocale(locale);
        doubleValidator->setNotation(QDoubleValidator::StandardNotation);
        dialog->setLineEditValidator(i + 7, doubleValidator);
        dialog->setLineEditPlaceholder(i + 7, "от 1 до 99.999");

        doubleValidator = new QDoubleValidator(1, 99.999, 3);
        doubleValidator->setLocale(locale);
        doubleValidator->setNotation(QDoubleValidator::StandardNotation);
        dialog->setLineEditValidator(i + 8, doubleValidator);
        dialog->setLineEditPlaceholder(i + 8, "от 1 до 99.999");
    }
    else {
        dialog->setLabelNames(getLowerTableHeaderNames());
        dialog->setEmptyLineEdits(getLowerTableHeaderNames().size() - 1);
        dialog->setAddDialComboBox1Values(getToBeAddedColumnValues());

        if (directoryList->currentItem() == directoryList->item(0)) {
            intValidator = new QIntValidator(10, 1000);
            dialog->setLineEditValidator(0, intValidator);
            dialog->setLineEditPlaceholder(0, "от 10 до 1000");

            intValidator = new QIntValidator(10, 999);
            dialog->setLineEditValidator(1, intValidator);
            dialog->setLineEditPlaceholder(1, "от 10 до 999");

            intValidator = new QIntValidator(10, 999);
            dialog->setLineEditValidator(2, intValidator);
            dialog->setLineEditPlaceholder(2, "от 10 до 999");
        }
        else if (directoryList->currentItem() == directoryList->item(1)) {
            doubleValidator = new QDoubleValidator(0.01, 1, 2);
            doubleValidator->setLocale(locale);
            doubleValidator->setNotation(QDoubleValidator::StandardNotation);
            dialog->setLineEditValidator(0, doubleValidator);
            dialog->setLineEditPlaceholder(0, "от 0.01 до 1");
        }
        else if (directoryList->currentItem() == directoryList->item(3)) {
            intValidator = new QIntValidator(10, 10000);
            dialog->setLineEditValidator(0, intValidator);
            dialog->setLineEditPlaceholder(0, "от 10 до 10000");

            intValidator = new QIntValidator(10, 10000);
            dialog->setLineEditValidator(1, intValidator);
            dialog->setLineEditPlaceholder(1, "от 10 до 10000");
        }
    }

    if (dialog->exec() == QDialog::Accepted) {
        if (directoryList->currentItem() == directoryList->item(2)) {
            QSqlQuery query;
            QString selectCurrent = "SELECT t1.termhierarchy, t2.termhierarchy, t3.termhierarchy FROM "
                                    "reference_data.terms t1, reference_data.terms t2, reference_data.terms t3 "
                                    "WHERE t1.termname = '%1' AND t2.termname = '%2' AND t3.termname = '%3'";
            QString selectCurrentQuery = selectCurrent.arg(dialog->getCurrentAddDialCB1Text())
                    .arg(dialog->getCurrentAddDialCB2Text()).arg(dialog->getCurrentAddDialCB3Text());

            query.exec(selectCurrentQuery);
            query.next();
            QString currentObject = query.value(0).toString();
            QString currentDegree = query.value(1).toString();
            QString currentRocket = query.value(2).toString();

            QString insertPattern = "INSERT INTO target_distribution.damage_regulations (obj_name, degree_name, "
                                    "rocket_type, quantity) VALUES ('%1', '%2', '%3', %4)";
            QString insertQuery = insertPattern.arg(currentObject).arg(currentDegree)
                    .arg(currentRocket).arg(dialog->getCurrentFieldText(0));

            if (!query.exec(insertQuery)) {
                qDebug() << "Unable to make insert operation\n" << query.lastError();
                QMessageBox::critical(this, "Ошибка", "Добавить данные не удалось!");
            }
            else {
                QMessageBox::information(this, "Уведомление", "Добавление прошло успешно!");
                slotShowDirectoryInfo(directoryList->currentItem());
            }
        }
        else if (directoryList->currentItem() == directoryList->item(4)) {
            QSqlQuery query;
            QString insertPattern = "INSERT INTO target_distribution.fire_table (obj_height, target_distance, "
                                    "launch_angle, flight_time, trajectory_maxheight, engine_drop_default, "
                                    "engine_drop_min, engine_drop_max, separation_time_min, "
                                    "separation_time_max) VALUES (%1, %2, %3, %4, %5, %6, %7, %8, %9, %10)";
            QString insertQuery;
            if (upperTable->hasFocus()) {
                insertQuery = insertPattern.arg(dialog->getCurrentAddDialCB1Text()).arg(dialog->getCurrentFieldText(0))
                        .arg(dialog->getCurrentFieldText(1)).arg(dialog->getCurrentFieldText(2))
                        .arg(dialog->getCurrentFieldText(3)).arg(dialog->getCurrentFieldText(4))
                        .arg(dialog->getCurrentFieldText(5)).arg(dialog->getCurrentFieldText(6))
                        .arg(dialog->getCurrentFieldText(7)).arg(dialog->getCurrentFieldText(8));
            }
            else {
                insertQuery = insertPattern.arg(dialog->getCurrentFieldText(0)).arg(dialog->getCurrentFieldText(1))
                        .arg(dialog->getCurrentFieldText(2)).arg(dialog->getCurrentFieldText(3))
                        .arg(dialog->getCurrentFieldText(4)).arg(dialog->getCurrentFieldText(5))
                        .arg(dialog->getCurrentFieldText(6)).arg(dialog->getCurrentFieldText(7))
                        .arg(dialog->getCurrentFieldText(8)).arg(dialog->getCurrentFieldText(9));
            }

            if (!query.exec(insertQuery)) {
                qDebug() << "Unable to make insert operation\n" << query.lastError();
                QMessageBox::critical(this, "Ошибка", "Добавить данные не удалось!");
            }
            else {
                QMessageBox::information(this, "Уведомление", "Добавление прошло успешно!");
                slotShowDirectoryInfo(directoryList->currentItem());
                upperTable->setCurrentItem(upperTable->item(dialog->getCurrentAddDialCB1Index(), 0));
            }
        }
        else {
            QSqlQuery query;

            QString insertPattern;
            QString insertQuery;

            if (directoryList->currentItem() == directoryList->item(0)) {
                insertPattern = "INSERT INTO target_distribution.warhead_characteristics "
                                "(rocket_type, attack_range, deviation_range, deviation_lateral) "
                                "VALUES ((SELECT termhierarchy FROM reference_data.terms WHERE "
                                "termname = '%1'), %2, %3, %4)";
                insertQuery = insertPattern.arg(dialog->getCurrentAddDialCB1Text()).arg(dialog->getCurrentFieldText(0))
                        .arg(dialog->getCurrentFieldText(1)).arg(dialog->getCurrentFieldText(2));
            }
            else if (directoryList->currentItem() == directoryList->item(1)) {
                insertPattern = "INSERT INTO target_distribution.damage_degree (degree_name, value) "
                                "VALUES ((SELECT termhierarchy FROM reference_data.terms WHERE "
                                "termname = '%1'), %2)";
                insertQuery = insertPattern.arg(dialog->getCurrentAddDialCB1Text()).arg(dialog->getCurrentFieldText(0));
            }
            else if (directoryList->currentItem() == directoryList->item(3)) {
                insertPattern = "INSERT INTO target_distribution.target_size (target_name, front, depth) "
                                "VALUES ((SELECT termhierarchy FROM reference_data.terms WHERE "
                                "termname = '%1'), %2, %3)";
                insertQuery = insertPattern.arg(dialog->getCurrentAddDialCB1Text()).arg(dialog->getCurrentFieldText(0))
                        .arg(dialog->getCurrentFieldText(1));
            }

            if (!query.exec(insertQuery)) {
                qDebug() << "Unable to make insert operation\n" << query.lastError();
                QMessageBox::critical(this, "Ошибка", "Добавить данные не удалось!");
            }
            else {
                QMessageBox::information(this, "Уведомление", "Добавление прошло успешно!");
                slotShowDirectoryInfo(directoryList->currentItem());
            }
        }
    }
    dialog->closeKeyboard();
}

void Editor::slotEdit() {
    dialog->setWindowTitle(directoryList->currentItem()->text());
    dialog->openKeyboard();

    if (directoryList->currentItem() == directoryList->item(4)) {
        dialog->setEditDialComboBox1Values(getUpperTableColumnValues());
        dialog->setLabelNames(getAllTableHeaderNames());
    }
    else {
        dialog->setLabelNames(getLowerTableHeaderNames());
        dialog->setEditDialComboBox1Values(getToBeEditedColumnValues());
    }

    if (dialog->exec() == QDialog::Accepted) {
        QSqlQuery query;
        QString updatePattern;
        QString updateQuery;

        if (directoryList->currentItem() == directoryList->item(0)) {
            updatePattern = "UPDATE target_distribution.warhead_characteristics w SET attack_range = %1, "
                            "deviation_range = %2, deviation_lateral = %3 FROM reference_data.terms t "
                            "WHERE t.termhierarchy = w.rocket_type AND t.termname = '%4'";
            updateQuery = updatePattern.arg(dialog->getCurrentFieldText(0)).arg(dialog->getCurrentFieldText(1))
                    .arg(dialog->getCurrentFieldText(2)).arg(dialog->getCurrentMainComboBoxText());
        }

        else if (directoryList->currentItem() == directoryList->item(1)) {
            updatePattern = "UPDATE target_distribution.damage_degree dd SET value = %1 FROM "
                            "reference_data.terms t WHERE t.termhierarchy = dd.degree_name "
                            "AND t.termname = '%2'";
            updateQuery = updatePattern.arg(dialog->getCurrentFieldText(0))
                    .arg(dialog->getCurrentMainComboBoxText());
        }

        else if (directoryList->currentItem() == directoryList->item(2)) {
            updatePattern = "UPDATE target_distribution.damage_regulations ts SET quantity = %1 "
                            "FROM reference_data.terms t1, reference_data.terms t2, "
                            "reference_data.terms t3 WHERE t1.termhierarchy = ts.obj_name AND "
                            "t1.termname = '%2' AND t2.termhierarchy = ts.degree_name "
                            "AND t2.termname = '%3' AND t3.termhierarchy = ts.rocket_type AND "
                            "t3.termname = '%4'";
            updateQuery = updatePattern.arg(dialog->getCurrentFieldText(0))
                    .arg(dialog->getCurrentMainComboBoxText()).arg(dialog->getCurrentSecondComboBoxText())
                    .arg(dialog->getCurrentThirdComboBoxText());
        }

        else if (directoryList->currentItem() == directoryList->item(3)) {
            updatePattern = "UPDATE target_distribution.target_size ts SET front = %1, depth = %2 "
                            "FROM reference_data.terms t WHERE t.termhierarchy = ts.target_name "
                            "AND t.termname = '%3'";
            updateQuery = updatePattern.arg(dialog->getCurrentFieldText(0))
                    .arg(dialog->getCurrentFieldText(1)).arg(dialog->getCurrentMainComboBoxText());
        }

        else if (directoryList->currentItem() == directoryList->item(4)) {
            updatePattern = "UPDATE target_distribution.fire_table f SET launch_angle = %1, "
                            "flight_time = %2, trajectory_maxheight = %3, engine_drop_default = %4, "
                            "engine_drop_min = %5, engine_drop_max = %6, separation_time_min = %7, "
                            "separation_time_max = %8 WHERE obj_height = %9 AND target_distance = %10";
            updateQuery = updatePattern.arg(dialog->getCurrentFieldText(0)).arg(dialog->getCurrentFieldText(1))
                    .arg(dialog->getCurrentFieldText(2)).arg(dialog->getCurrentFieldText(3))
                    .arg(dialog->getCurrentFieldText(4)).arg(dialog->getCurrentFieldText(5))
                    .arg(dialog->getCurrentFieldText(6)).arg(dialog->getCurrentFieldText(7))
                    .arg(dialog->getCurrentMainComboBoxText()).arg(dialog->getCurrentSecondComboBoxText());
        }

        if (!query.exec(updateQuery)) {
            qDebug() << "Unable to make update operation\n" << query.lastError();
            QMessageBox::critical(this, "Ошибка", "Обновить данные не удалось!");
        }
        else {
            QMessageBox::information(this, "Уведомление", "Обновление прошло успешно!");
            slotShowDirectoryInfo(directoryList->currentItem());
            upperTable->setCurrentItem(upperTable->item(dialog->getMainComboBoxCurrentIndex(), 0));
        }
    }
    dialog->closeKeyboard();
}

void Editor::slotDelete() {  
    if (directoryList->currentItem() == directoryList->item(2)) {
        QString classifierName1 = lowerTable->item(lowerTable->currentRow(), 0)->text();
        QString classifierName2 = lowerTable->item(lowerTable->currentRow(), 1)->text();
        QString classifierName3 = lowerTable->item(lowerTable->currentRow(), 2)->text();

        QSqlQuery query;
        QString selectPattern = "SELECT t1.termhierarchy, t2.termhierarchy, t3.termhierarchy FROM "
                                "reference_data.terms t1, reference_data.terms t2, reference_data.terms t3 "
                                "WHERE t1.termname = '%1' AND t2.termname = '%2' AND t3.termname = '%3'";
        QString selectQuery = selectPattern.arg(classifierName1).arg(classifierName2).arg(classifierName3);
        query.exec(selectQuery);

        QStringList classifierIds;
        query.next();
        classifierIds.append(query.value(0).toString());
        classifierIds.append(query.value(1).toString());
        classifierIds.append(query.value(2).toString());

        QString deletePattern = "DELETE FROM target_distribution.damage_regulations WHERE obj_name = '%1' "
                                "AND degree_name = '%2' AND rocket_type = '%3'";
        QString deleteQuery = deletePattern.arg(classifierIds.at(0)).arg(classifierIds.at(1)).arg(classifierIds.at(2));

        if (!query.exec(deleteQuery)) {
            qDebug() << "Unable to make delete operation\n" << query.lastError();
            QMessageBox::critical(this, "Ошибка", "Удалить данные не удалось!");
        }
        else {
            QMessageBox::information(this, "Уведомление", "Удаление прошло успешно!");
            slotShowDirectoryInfo(directoryList->currentItem());
        }
    }
    else if (directoryList->currentItem() == directoryList->item(4)) {
        QSqlQuery query;
        QString deletePattern;
        QString deleteQuery;

        if (upperTable->hasFocus()) {
            deletePattern = "DELETE FROM target_distribution.fire_table WHERE obj_height = %1";
            deleteQuery = deletePattern.arg(upperTable->item(upperTable->currentRow(), 0)->text());
        }
        else if (lowerTable->hasFocus()) {
            deletePattern = "DELETE FROM target_distribution.fire_table WHERE obj_height = %1 AND "
                            "target_distance = %2";
            deleteQuery = deletePattern.arg(upperTable->item(upperTable->currentRow(), 0)->text())
                    .arg(lowerTable->item(lowerTable->currentRow(), 0)->text());
        }

        if (!query.exec(deleteQuery)) {
            qDebug() << "Unable to make delete operation\n" << query.lastError();
            QMessageBox::critical(this, "Ошибка", "Удалить данные не удалось!");
        }
        else {
            QMessageBox::information(this, "Уведомление", "Удаление прошло успешно!");
            if (lowerTable->hasFocus()) {
                slotShowLowerFireTable();
                editAction->setEnabled(false);
                deleteAction->setEnabled(false);
            }
            else {
                slotShowDirectoryInfo(directoryList->currentItem());
            }
        }
    }
    else {
        QString classifierName = lowerTable->item(lowerTable->currentRow(), 0)->text();
        QSqlQuery query;
        QString selectPattern = "SELECT termhierarchy FROM reference_data.terms WHERE termname = '%1'";
        QString selectQuery = selectPattern.arg(classifierName);
        query.exec(selectQuery);
        query.next();
        QString classifierId = query.value(0).toString();

        QString deletePattern;

        if (directoryList->currentItem() == directoryList->item(0)) {
            deletePattern = "DELETE FROM target_distribution.warhead_characteristics WHERE rocket_type = '%1'";
        }
        else if (directoryList->currentItem() == directoryList->item(1)) {
            deletePattern = "DELETE FROM target_distribution.damage_degree WHERE degree_name = '%1'";
        }
        else if (directoryList->currentItem() == directoryList->item(3)) {
            deletePattern = "DELETE FROM target_distribution.target_size WHERE target_name = '%1'";
        }

        QString deleteQuery = deletePattern.arg(classifierId);

        if (!query.exec(deleteQuery)) {
            qDebug() << "Unable to make delete operation\n" << query.lastError();
            QMessageBox::critical(this, "Ошибка", "Удалить данные не удалось!");
        }
        else {
            QMessageBox::information(this, "Уведомление", "Удаление прошло успешно!");
            slotShowDirectoryInfo(directoryList->currentItem());
        }
    }
}

QStringList Editor::getLowerTableHeaderNames() {
    QStringList list;
    for (int i = 0; i < lowerTable->columnCount(); i++) {
        list.append(lowerTable->horizontalHeaderItem(i)->text());
    }
    return list;
}

QStringList Editor::getAllTableHeaderNames() {
    QStringList list;
    list.append(upperTable->horizontalHeaderItem(0)->text());
    list.append(getLowerTableHeaderNames());
    return list;
}

QStringList Editor::getToBeAddedColumnValues() {
    QSqlQuery query;
    QString selectPattern;

    if (directoryList->currentItem() == directoryList->item(0)) {
        selectPattern = "SELECT termname FROM reference_data.terms WHERE termhierarchy ~ '51.50.*' AND "
                        "termhierarchy NOT IN (SELECT rocket_type FROM target_distribution.warhead_characteristics)";
    }
    else if (directoryList->currentItem() == directoryList->item(1)) {
        selectPattern = "SELECT termname FROM reference_data.terms WHERE termhierarchy ~ '95.10.*' AND "
                        "termhierarchy NOT IN (SELECT degree_name FROM target_distribution.damage_degree)";
    }
    else if (directoryList->currentItem() == directoryList->item(2)) {
        selectPattern = "SELECT termname FROM reference_data.terms WHERE termhierarchy ~ '90.*' AND "
                        "termhierarchy != '90.10' AND termhierarchy != '90.20' AND termhierarchy != '90.30'";
    }
    else if (directoryList->currentItem() == directoryList->item(3)) {
        selectPattern = "SELECT termname FROM reference_data.terms WHERE termhierarchy ~ '90.20.*' AND "
                        "termhierarchy NOT IN (SELECT target_name FROM target_distribution.target_size)";
    }
    query.exec(selectPattern);
    query.next(); // exclude parent

    QStringList list;
    while (query.next()) {
        list.append(query.value(0).toString());
    }
    return list;
}

QStringList Editor::getToBeEditedColumnValues() {
    QStringList list;
    for (int i = 0; i < lowerTable->rowCount(); i++) {
        if (!list.contains(lowerTable->item(i, 0)->text())) {
            list.append(lowerTable->item(i, 0)->text());
        }
    }
    return list;
}

QStringList Editor::getUpperTableColumnValues() {
    QStringList list;
    for (int i = 0; i < upperTable->rowCount(); i++) {
        list.append(upperTable->item(i, 0)->text());
    }
    return list;
}
