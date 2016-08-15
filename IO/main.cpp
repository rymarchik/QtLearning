#include "printer.h"
#include "fileFinder.h"
#include "fileWatcher.h"

int main(int argc, char *argv[])
{
//------------------------------------------------------------------------      QFile & QTextStream
    QApplication app(argc, argv);
//    Printer p;
    QFile file1(":/input.txt");
//    file1.setFileName("input.txt");
    QFile file2("output.txt");
    QString string = "text for file2!";

    if (file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file1);
        QString str;
        str = stream.readAll();
//        while (!stream.atEnd()) {
//            str = stream.readLine();
//            qDebug() << str;
//        }
        qDebug() << str;

        if (stream.status() != QTextStream::Ok) {
            qDebug() << "Ошибка чтения";
        }
        file1.close();
    }
    if (file2.open(QIODevice::Append)) {
        QTextStream stream(&file2);
        stream << string.toUpper();
        if (stream.status() != QTextStream::Ok) {
            qDebug() << "Ошибка записи";
        }
        file2.close();
    }

//    QByteArray arr = file1.readAll();
//    file2.write(arr);

//    char a[1024];
//    while(!file1.atEnd()) {
//        int blocksize = file1.read(a, sizeof(a));
//        file2.write(a, blocksize);
//    }

    p.print(&file2);

//    qDebug() << file2.isOpen() << file2.fileName();
//    qDebug() << QFile::exists("output.txt") << file2.exists();
//------------------------------------------------------------------------      QDataStream
    QFile file3("binary.bin");
    if (file3.open(QIODevice::WriteOnly)) {
        QDataStream stream(&file3);
        stream << QPixmap(":/fileopen.png");
        if (stream.status() != QDataStream::Ok) {
            qDebug() << "Ошибка записи";
        }
    }
    file3.close();

    QPixmap img;
    QLabel lbl;
    if (file3.open(QIODevice::ReadOnly)) {
        QDataStream stream(&file3);
        stream >> img;
        lbl.setPixmap(img);
        if (stream.status() != QDataStream::Ok) {
            qDebug() << "Ошибка чтения";
        }
    }
    file3.close();

    lbl.resize(300,300);
//    lbl.show();
//------------------------------------------------------------------------      QBuffer
//    QPixmap img;
//    QLabel lbl;
//    QByteArray array;
//    QBuffer buffer(&array);
//    buffer.open(QIODevice::WriteOnly);
//    QDataStream stream(&buffer);
//    stream << QPixmap(":/fileopen.png");
//    buffer.open(QIODevice::ReadOnly);
//    stream >> img;
//    lbl.setPixmap(img);
//    buffer.close();
//    lbl.resize(300,300);
//    lbl.show();
//------------------------------------------------------------------------      QFileInfo
    QFileInfo info1("C:/Rymarchik/Volat/projects/IO/input.txt");
    QFileInfo info2(file2);
    qDebug() << info1.created().toString() << info1.completeSuffix() << info1.size();
    qDebug() << info2.lastModified().toString() << info2.isSymLink()
             << info2.isReadable() << info2.isWritable() << info2.isExecutable();


//------------------------------------------------------------------------      FileFinder

    FileFinder f;
//    f.show();
//------------------------------------------------------------------------      FileWatcher

    QFileSystemWatcher watcher;
    FileWatcher viewer;

    watcher.addPath("C:/Rymarchik/Volat/projects/IO");
    watcher.addPath("C:/Rymarchik/Volat/projects/IO/input.txt");

    viewer.append("Watching files:" + watcher.files().join(";"));
    viewer.append("Watching directories:" + watcher.directories().join(";"));

    QObject::connect(&watcher, SIGNAL(fileChanged(QString)), &viewer, SLOT(slotFileChanged(QString)));
    QObject::connect(&watcher, SIGNAL(directoryChanged(QString)), &viewer, SLOT(slotDirChanged(QString)));

//    viewer.show();

    return app.exec();
}
