#include "widget.h"
#include <QtSql>
#include <QApplication>

static bool createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//    db.setDatabaseName("postgres");
//    db.setUserName("postgres");
//    db.setPassword("root");
//    db.setHostName("localhost");



    db.setDatabaseName("A200");
    db.setUserName("postgres");
    db.setPassword("qwerty");
    db.setHostName("192.168.1.42");
    db.setPort(5432);

    if (!db.open()) {
        qDebug() << "Can't open database: " << db.lastError();
        return false;
    }
    QStringList tables = db.tables();
    foreach (QString table, tables) {
        qDebug() << "Table: " << table;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection()) {
        return -1;
    }

//    QSqlQuery query;

//    QString createDb = "create table Roommates(id integer primary key not null, name varchar(10), age integer(3))";
//    if (!query.exec(createDb)) {
//        qDebug() << "Unable to create a table";
//    }

//    QString insertInfo = "insert into Roommates(id, name, email) values(?,?,?)";
//    query.prepare(insertInfo);
//    query.addBindValue(1);
//    query.addBindValue("Alex");
//    query.addBindValue(22);
//    if (!query.exec(insertInfo)) {
//        qDebug() << "Unable to make insert operation";
//    }
//    query.addBindValue(2);
//    query.addBindValue("Olga");
//    query.addBindValue(27);
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
