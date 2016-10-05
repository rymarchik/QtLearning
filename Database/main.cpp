#include "widget.h"
#include <QtSql>
#include <QApplication>

static bool createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("root");
    db.setHostName("localhost");

//    db.setDatabaseName("A200");
//    db.setUserName("asrymarchik");
//    db.setPassword("123456");
//    db.setHostName("192.168.1.42");
    db.setPort(5432);

    if (!db.open()) {
        qDebug() << "Can't open database: " << db.lastError();
        return false;
    }
//    QStringList tables = db.tables();
//    foreach (QString table, tables) {
//        qDebug() << "Table: " << table;
//    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection()) {
        return -1;
    }

    QSqlQuery query;

    QString createDb = "CREATE TABLE Location (id INTEGER primary key not null, latitude real, longitude real, altitude real, time time)";
    if (!query.exec(createDb)) {
        qDebug() << "Unable to create a table";
    }

//    double lat = 55.01;
//    QDateTime time = QDateTime::currentDateTime();
//    QString insertInfo = "INSERT INTO location (id, latitude, time) VALUES(%1, %2, '%3');";
//    QString str = insertInfo.arg("8").arg(lat).arg(time.toString("hh:mm:ss"));

//    if (!query.exec(str)) {
//        qDebug() << "Unable to make insert operation";
//    }
//    query.prepare(insertInfo);
//    query.addBindValue(2);
//    query.addBindValue(55.02);
//    query.addBindValue(27.02);
//    query.addBindValue(250.2);
//    query.addBindValue("09:00:01");
//    if (!query.exec(insertInfo)) {
//        qDebug() << "Unable to make insert operation";
//    }

//    if (!query.exec("select * from Roommates;")) {
//        qDebug() << "Unable to execute query";
//        return 1;
//    }

//    QSqlRecord rec = query.record();
//    int id;
//    QString name;
//    int age;

//    while(query.next()) {
//        id = query.value(rec.indexOf("id")).toInt();
//        name = query.value(rec.indexOf("name")).toString();
//        age = query.value(rec.indexOf("age")).toInt();
//        qDebug() << id << " " << name << " " << age;
//    }

    return a.exec();
}
