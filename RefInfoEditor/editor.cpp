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

    setCentralWidget(contentWindow);
    setWindowIcon(QIcon(":/resources/title.png"));
    setWindowTitle("Редактор нормативно-справочной информации");

    connect(addAction, SIGNAL(triggered()), this, SLOT(slotAdd()));
    connect(editAction, SIGNAL(triggered()), this, SLOT(slotEdit()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(slotDelete()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Editor::slotShowDirectoryInfo(QListWidgetItem* dirItem) {
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
                << "Максимальная высота\n траектории, м" << "Место падения двигателя\n по умолчанию, м"
                << "Минимальное расстояние места\n падения двигателя, м"
                << "Максимальное расстояние места\n падения двигателя, м"
                << "Минимальное время\n разделения, с" << "Максимальное время\n разделения, с";
    lowerTable->setHorizontalHeaderLabels(headerNames);

    lowerTableHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void Editor::slotChangeRootItemValue(int n) {
    if (n != -1) {
        if (directoryList->currentItem() == directoryList->item(2)) {
            QStringList list;
            for (int i = 0; i < lowerTable->rowCount(); i++) {
                if (lowerTable->item(i, 0)->text() == dialog->getCurrentMainComboBoxText())
                    if (!list.contains(lowerTable->item(i, 1)->text()))
                        list.append(lowerTable->item(i, 1)->text());
            }
            qDebug() << list;
            dialog->setSecondComboBoxValues(list);

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
            if (upperTable->hasFocus()) {
                dialog->setMainComboBoxCurrentIndex(upperTable->currentRow());
            }
            else {
                upperTable->setCurrentItem(upperTable->item(n, 0));
            }
            QStringList list = getRootColumnValues();
            qDebug() << list;
            dialog->setSecondComboBoxValues(list);
        }
        else {
            QStringList list;
            for (int i = 0; i < lowerTable->columnCount() - 1; i++) {
                list.append(lowerTable->item(n, i + 1)->text());
            }
            dialog->fillFieldList(list);
            dialog->placeFieldList(list.size());
        }
    }
}

void Editor::slotChange2ndRootItemValue(int n) {
    if (n != -1) {
        if (directoryList->currentItem() == directoryList->item(2)) {
            QStringList list;
            for (int i = 0; i < lowerTable->rowCount(); i++) {
                if (lowerTable->item(i, 0)->text() == dialog->getCurrentMainComboBoxText())
                   if (lowerTable->item(i, 1)->text() == dialog->getCurrentSecondComboBoxText())
                       list.append(lowerTable->item(i, 2)->text());
            }
            qDebug() << list;
            dialog->setThirdComboBoxValues(list);
        }
        else if (directoryList->currentItem() == directoryList->item(4)) {
            QStringList list;
            for (int i = 0; i < lowerTable->columnCount() - 1; i++) {
                list.append(lowerTable->item(n, i + 1)->text());
            }
            qDebug() << list;
            dialog->fillFieldList(list);
            dialog->placeFieldList(list.size());
        }
    }
}

void Editor::slotChange3rdRootItemValue(int n) {
    if (n != -1) {
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
    }
}

void Editor::slotAdd() {
    dialog->setWindowTitle(directoryList->currentItem()->text());

    if (directoryList->currentItem() == directoryList->item(4)) {
        upperTable->setCurrentItem(upperTable->item(0, 0));
        dialog->setLabelNames(getAllTableHeaderNames());
        dialog->setEmptyLineEdits(getAllTableHeaderNames().size());
    }
    else {
        dialog->setLabelNames(getLowerTableHeaderNames());
        dialog->setEmptyLineEdits(getLowerTableHeaderNames().size());
    }

    if (dialog->exec() == QDialog::Accepted) {
        if (directoryList->currentItem() == directoryList->item(2)) {

        }
        else if (directoryList->currentItem() == directoryList->item(4)) {
            QSqlQuery query;
            QString insertPattern = "INSERT INTO target_distribution.fire_table (obj_height, target_distance, "
                                    "launch_angle, flight_time, trajectory_maxheight, engine_drop_default, "
                                    "engine_drop_min, engine_drop_max, separation_time_min, "
                                    "separation_time_max) VALUES (%1, %2, %3, %4, %5, %6, %7, %8, %9, %10)";
            QString insertQuery = insertPattern.arg(dialog->getCurrentFieldText(0)).arg(dialog->getCurrentFieldText(1))
                    .arg(dialog->getCurrentFieldText(2)).arg(dialog->getCurrentFieldText(3))
                    .arg(dialog->getCurrentFieldText(4)).arg(dialog->getCurrentFieldText(5))
                    .arg(dialog->getCurrentFieldText(6)).arg(dialog->getCurrentFieldText(7))
                    .arg(dialog->getCurrentFieldText(8)).arg(dialog->getCurrentFieldText(9));

            if (!query.exec(insertQuery)) {
                qDebug() << "Unable to make insert operation";
            }
            else {
                QMessageBox::information(this, "Уведомление", "Обновление прошло успешно!");
            }
        }
        else {
            QSqlQuery query;

            QString insertPattern;
            QString insertQuery;
            QString insertPattern2 = "INSERT INTO reference_data.terms (termhierarchy, termname, termshortname, "
                                     "termsrule) VALUES ('%1', '%2', '', 0)";
            QString insertQuery2;

            if (directoryList->currentItem() == directoryList->item(0)) {
                insertPattern = "INSERT INTO target_distribution.warhead_characteristics "
                                "(rocket_type, attack_range, deviation_range, deviation_lateral) "
                                "VALUES ('%1', %2, %3, %4)";
                insertQuery = insertPattern.arg("11.11.11.11").arg(dialog->getCurrentFieldText(1))
                        .arg(dialog->getCurrentFieldText(2)).arg(dialog->getCurrentFieldText(3));

                insertQuery2 = insertPattern2.arg("11.11.11.11").arg(dialog->getCurrentFieldText(0));
            }
            else if (directoryList->currentItem() == directoryList->item(1)) {
                insertPattern = "INSERT INTO target_distribution.damage_degree "
                                "(degree_name, value) VALUES ('%1', %2)";
                insertQuery = insertPattern.arg("22.22.22.22").arg(dialog->getCurrentFieldText(1));

                insertQuery2 = insertPattern2.arg("22.22.22.22").arg(dialog->getCurrentFieldText(0));
            }
            else if (directoryList->currentItem() == directoryList->item(3)) {
                insertPattern = "INSERT INTO target_distribution.target_size "
                                "(target_name, front, depth) VALUES ('%1', %2, %3)";
                insertQuery = insertPattern.arg("44.44.44.44").arg(dialog->getCurrentFieldText(1))
                        .arg(dialog->getCurrentFieldText(2));

                insertQuery2 = insertPattern2.arg("44.44.44.44").arg(dialog->getCurrentFieldText(0));
            }

            db.transaction();
            if (!query.exec(insertQuery)) {
                qDebug() << "Unable to make 1st insert operation";
            }
            if (!query.exec(insertQuery2)) {
                qDebug() << "Unable to make 2nd insert operation";
            }
            if (db.commit()) {
                QMessageBox::information(this, "Уведомление", "Добавление прошло успешно!");
//                slotShowDirectoryInfo();
            }
        }
    }
}

void Editor::slotEdit() {
    dialog->setWindowTitle(directoryList->currentItem()->text());

    if (directoryList->currentItem() == directoryList->item(4)) {
        dialog->setMainComboBoxValues(getUpperTableColumnValues());
        dialog->setLabelNames(getAllTableHeaderNames());
    }
    else {
        dialog->setLabelNames(getLowerTableHeaderNames());
        dialog->setMainComboBoxValues(getRootColumnValues());
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
            qDebug() << "Unable to make update operation";
        }
        else {
            QMessageBox::information(this, "Уведомление", "Обновление прошло успешно!");
        }
    }
}

void Editor::slotDelete() {  
    if (directoryList->currentItem() == directoryList->item(2)) {

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
            qDebug() << "Unable to make delete operation";
        }
        else {
            QMessageBox::information(this, "Уведомление", "Удаление прошло успешно!");
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
        QString deletePattern2 = "DELETE FROM reference_data.terms WHERE termhierarchy = '%1'";
        QString deleteQuery2 = deletePattern2.arg(classifierId);

        db.transaction();
        if (!query.exec(deleteQuery)) {
            qDebug() << "Unable to make 1st delete operation";
        }
        if (!query.exec(deleteQuery2)) {
            qDebug() << "Unable to make 2nd delete operation";
        }
        if (db.commit()) {
            QMessageBox::information(this, "Уведомление", "Удаление прошло успешно!");
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

QStringList Editor::getRootColumnValues() {
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
