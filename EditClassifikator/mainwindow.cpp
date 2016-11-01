#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "dlgdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dlgDialog(new dlgDialog(this))
{
    ui->setupUi(this);

    //1// Соединение с БД:
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("192.168.1.42");
    db.setPort(5432);
    db.setDatabaseName("A200");
    db.setUserName("oiderenchuk");
    db.setPassword("klop1331!");

    if (!db.open())
    {
        qDebug() << db.lastError().text();
    }
    else
    {
        qDebug() << "Success!";
    }

    //2// События:
    // Выбрано меню из toolbar:
    slotRefresh();
    connect( ui->m_Add,     SIGNAL (triggered()),  this, SLOT (slotAdd())        );
    connect( ui->m_Edit,    SIGNAL (triggered()),  this, SLOT (slotEdit())       );
    connect( ui->m_Delete,  SIGNAL (triggered()),  this, SLOT (slotDelete())     );
    connect( ui->m_Exit,    SIGNAL (triggered()),  this, SLOT (slotSave())       );
    connect( ui->m_Find,    SIGNAL (triggered()),  this, SLOT (slotFind())       );
    connect( ui->m_Refresh, SIGNAL (triggered()),  this, SLOT (slotRefresh())    );

    //connect( ui->treeWidget,SIGNAL (itemClicked()),ui->treeWidget, SLOT (slotGetParam())   );
    //connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *)), this, SLOT(slotGetParam()));
    //connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *)), this, SLOT(slotGetParam()));
    connect( m_dlgDialog,   SIGNAL (rejected()),   this, SLOT (slotDlgRejected()));
    connect( m_dlgDialog,   SIGNAL (accepted()),   this, SLOT (slotDlgAccepted()));
    //2;//
}

void MainWindow::slotGetParam()
{
    QList<QTreeWidgetItem *> itemSelect;
    itemSelect = ui->treeWidget->selectedItems();
    for (int i = 0; i < itemSelect.count(); i++)
    {
        m_textTermname = itemSelect.at(i)->text(0);
        m_textTermhierarchy = itemSelect.at(i)->text(1);
        m_textTermshortname = itemSelect.at(i)->text(2);
        qDebug() << "itemSelect: " << m_textTermname << m_textTermhierarchy << m_textTermshortname;
    }
}

//Выгрузка данных БД в TreeWidget:
void MainWindow::slotRefresh()
{
    QSqlQuery sql = QSqlQuery(db);
    if (!sql.exec("SELECT * from reference_data.terms"))
    {
        qDebug() << sql.lastError().databaseText();
        return;
    }

    QStringList list;
    ui->treeWidget->clear();
    ui->treeWidget->setHeaderLabel("");

    QTreeWidgetItem *rootItem,*classifItem;
    QHash <QString,QTreeWidgetItem*> hashItems;

    list.clear();
    list << "Наименование понятия" << "Номер" << "Краткое название";
    rootItem = new QTreeWidgetItem(list);

    ui->treeWidget->setHeaderLabels(list);
    classifItem = rootItem;

    if (!sql.exec("SELECT termhierarchy, termshortname, termname, termsrule FROM reference_data.terms order by termhierarchy"))
    {
        db.rollback();
        QApplication::restoreOverrideCursor();
        QMessageBox::warning(this, tr("f"), sql.lastError().text());
        return;
    }

    while(sql.next())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0,sql.value(2).toString().trimmed());
        item->setToolTip(0, sql.value(2).toString().trimmed());
        item->setText(1, sql.value(0).toString().trimmed());
        item->setText(2, sql.value(1).toString().trimmed());

        //настройка ширины колонки(0, //1, 2):
        ui->treeWidget->resizeColumnToContents(0);
        //ui->treeWidget->resizeColumnToContents(1);
        ui->treeWidget->resizeColumnToContents(2);

        QString termhierarchy = sql.value(0).toString().trimmed();
        termhierarchy.contains(".", Qt::CaseInsensitive);
        QString sParentCode;
        if (!termhierarchy.contains(".", Qt::CaseInsensitive))
        {
            ui->treeWidget->addTopLevelItem(item);
            classifItem->addChild(item);
        }
        else
        {
            QString sCode = termhierarchy.right(2);
            int lendth=termhierarchy.length();
            lendth=lendth-3;
            sParentCode=termhierarchy.left(lendth);
            QHash <QString,QTreeWidgetItem*>::const_iterator i = hashItems.find(sParentCode);
            if (i != hashItems.end())
            {
                rootItem=i.value();
                rootItem->addChild(item);
                ui->treeWidget->collapseItem(rootItem);
            }
        }
        hashItems[termhierarchy] = item;
    }

    db.commit();
    //QSqlDatabase::database().commit();
    ui->treeWidget->sortByColumn(1, Qt::AscendingOrder);
    QApplication::restoreOverrideCursor();
    classifItem->setExpanded(true);
}

void MainWindow::slotAdd()
{
    m_dlgDialog->setWindowTitle(tr("Добавить"));
    numDialog = 1;
    showDialog();
    setWindowModified(true);
    return;
}

void MainWindow::slotEdit()
{
    m_dlgDialog->setWindowTitle(tr("Изменить"));
    numDialog = 2;

    QTreeWidgetItem* itemCurrent;
    itemCurrent = ui->treeWidget->currentItem();
    m_textTermname = itemCurrent->text(0);
    m_textTermhierarchy = itemCurrent->text(1);
    m_textTermshortname = itemCurrent->text(2);
    qDebug() << "itemCurrent: " << m_textTermname << m_textTermhierarchy << m_textTermshortname;

    m_dlgDialog->setTextLineEdit(m_textTermname, m_textTermhierarchy, m_textTermshortname);

    showDialog();
    setWindowModified(true);
    return;
}

void MainWindow::slotDelete()
{
    m_dlgDialog->setWindowTitle(tr("Удалить"));
    numDialog = 3;

    QTreeWidgetItem* itemCurrent;
    itemCurrent = ui->treeWidget->currentItem();
    m_textTermname = itemCurrent->text(0);
    m_textTermhierarchy = itemCurrent->text(1);
    m_textTermshortname = itemCurrent->text(2);
    qDebug() << "itemCurrent: " << m_textTermname << m_textTermhierarchy << m_textTermshortname;

    m_dlgDialog->setTextLineEdit(m_textTermname, m_textTermhierarchy, m_textTermshortname);

    showDialog();
    setWindowModified(true);
    return;
}

void MainWindow::slotFind()
{
    m_dlgDialog->setWindowTitle(tr("Найти"));
    numDialog = 4;
    showDialog();
    setWindowModified(true);
    return;
}

void MainWindow::slotDlgRejected()
{
    m_dlgDialog->killProcess();  
}

void MainWindow::slotDlgAccepted()
{
    m_dlgDialog->killProcess();

    qDebug() << "numDialog: "     << numDialog;
    qDebug() << "Termname: "      << m_dlgDialog->getLineEditTermname();
    qDebug() << "Termhierarchy: " << m_dlgDialog->getLineEditTermhierarchy();
    qDebug() << "Termshortname: " << m_dlgDialog->getLineEditTermshortname();

    switch (numDialog)
    {
      case 1://"Добавить"////////////////////////////////////////////////////////////////////////////////////
        query = QSqlQuery(db);
        if (!query.exec("SELECT * from reference_data.terms"))
        {
            qDebug() << query.lastError().databaseText();
            return;
        }
        db.transaction();
        query.prepare( "INSERT INTO reference_data.terms (termhierarchy, termname, termshortname, termsrule)"
                       "VALUES (?, ?, ?, ?)" );
        query.addBindValue( m_dlgDialog->getLineEditTermhierarchy() );
        query.addBindValue( m_dlgDialog->getLineEditTermname() );
        query.addBindValue( m_dlgDialog->getLineEditTermshortname() );
        query.addBindValue( 101 );
        query.exec();
        db.commit();

        slotRefresh();
        break;
      case 2: //"Изменить"////////////////////////////////////////////////////////////////////////////////////
        query = QSqlQuery(db);
        if (!query.exec("SELECT * from reference_data.terms"))
        {
            qDebug() << query.lastError().databaseText();
            return;
        }
        db.transaction();
        query.prepare( "UPDATE reference_data.terms "
                       "SET termhierarchy=?, termname=?, termshortname=? "
                       "WHERE termhierarchy=? AND termname=? AND termshortname=? " );
        query.addBindValue( m_dlgDialog->getLineEditTermhierarchy());
        query.addBindValue( m_dlgDialog->getLineEditTermname()     );
        query.addBindValue( m_dlgDialog->getLineEditTermshortname());

        query.addBindValue( m_textTermhierarchy );
        query.addBindValue( m_textTermname      );
        query.addBindValue( m_textTermshortname );

        query.exec();
        db.commit();
        slotRefresh();
        break;
      case 3://"Удалить"////////////////////////////////////////////////////////////////////////////////////
        query = QSqlQuery(db);
        if (!query.exec("SELECT * from reference_data.terms"))
        {
            qDebug() << query.lastError().databaseText();
            return;
        }
        db.transaction();
        query.prepare( "DELETE FROM reference_data.terms "
                        "WHERE termhierarchy = ? AND termname = ? AND termshortname = ?" );
        query.addBindValue( m_dlgDialog->getLineEditTermhierarchy() );
        query.addBindValue( m_dlgDialog->getLineEditTermname() );
        query.addBindValue( m_dlgDialog->getLineEditTermshortname() );
        query.exec();
        db.commit();
        slotRefresh();
        break;
      case 4://"Найти"////////////////////////////////////////////////////////////////////////////////////
        QList<QTreeWidgetItem *> ItemsFinded;
        ItemsFinded = ui->treeWidget->findItems(m_dlgDialog->getLineEditTermname(),
                                                Qt::MatchRecursive|Qt::MatchContains, 0); //поиск соответствий по всем child
        qDebug("Finded: %d ", ItemsFinded.count());
        for (int i = 0; i < ItemsFinded.count(); i++)
        {
            m_textTermhierarchy = ItemsFinded.at(i)->text(1);
            qDebug() << "Termhierarchy: " << m_textTermhierarchy;
            ItemsFinded.at(i)->setForeground(0, Qt::blue);
            for(int j=0; j < 100; j++)
            {
              ui->treeWidget->expandItem(ItemsFinded.at(i));   // раскрытие узла найденного эл-та
            }
        }
        break;
    }
}

void MainWindow::slotSave()
{
    if(isWindowModified())
    {
        int ok = QMessageBox::question(this, "question", QString("Save?"), QMessageBox::Ok | QMessageBox::No);
        if (ok == QMessageBox::Ok)
        {
            close();
            setWindowModified(false);
        }
    }
    else
    {
        close();
        setWindowModified(false);
    }    
}

void MainWindow::showDialog()
{
    m_dlgDialog->show();
    m_dlgDialog->startProcess();
}

MainWindow::~MainWindow()
{
    delete ui;    
}
