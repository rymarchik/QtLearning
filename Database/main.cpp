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
    db.setUserName("asrymarchik");
    db.setPassword("123456");
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

    QSqlQuery query;

//    QString createDb = "CREATE TABLE Location (id INTEGER primary key not null, latitude real, longitude real, altitude real, time time)";
//    if (!query.exec(createDb)) {
//        qDebug() << "Unable to create a table";
//    }

    double lon = 27.6;
    double lat = 66.01;
    double alt = 245;
    QDateTime time = QDateTime::currentDateTime();
    QString insertInfo = "INSERT INTO own_forces.combatobject_location (combatobjectid, obj_latitude, btime) VALUES(%1, %2, '%3');";
    QString ins = insertInfo.arg("1").arg(lat).arg(time.toString("hh:mm:ss"));

    QString updateInfo = "UPDATE own_forces.combatobject_location SET "
                         "obj_location = ST_SetSRID(ST_MakePoint(%1, %2, %3), 4326), btime = '%4' WHERE combatobjectid = %5;";
    QString upd = updateInfo.arg(lon).arg(lat).arg(alt).arg(time.toString("hh:mm:ss")).arg("1");

//    query.prepare(updateInfo);
//    query.addBindValue(lat);
//    query.bindValue(":time", time.toString("hh:mm:ss"));
//    query.addBindValue("1");

    if (!query.exec(upd)) {
        qDebug() << "Unable to make insert operation";
    }

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
