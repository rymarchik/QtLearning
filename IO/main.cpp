#include "printer.h"
#include "fileFinder.h"
#include "fileWatcher.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Printer p;
    QFile file1(":/input.txt");
//    file1.setFileName("input.txt");
    QFile file2("output.txt");

    if (!file1.open(QIODevice::ReadOnly)) {
        qDebug() << "Ошибка открытия для чтения";
    }
    if (!file2.open(QIODevice::WriteOnly)) {
        qDebug() << "Ошибка открытия для записи";
    }

//    QByteArray arr = file1.readAll();
//    file2.write(arr);

    char a[1024];
    while(!file1.atEnd()) {
        int blocksize = file1.read(a, sizeof(a));
        file2.write(a, blocksize);
    }

    file1.close();
    file2.close();
    p.print(&file2);

//    qDebug() << file2.isOpen() << file2.fileName();
//    qDebug() << QFile::exists("output.txt") << file2.exists();
//--------------------------------------------------------------------------------
    QFileInfo info1("C:/Rymarchik/Volat/projects/IO/input.txt");
    QFileInfo info2(file2);
    qDebug() << info1.created().toString() << info1.completeSuffix() << info1.size();
    qDebug() << info2.lastModified().toString() << info2.isSymLink()
             << info2.isReadable() << info2.isWritable() << info2.isExecutable();


//--------------------------------------------------------------------------------

    FileFinder f;
//    f.show();
//--------------------------------------------------------------------------------

    QFileSystemWatcher watcher;
    FileWatcher viewer;

    QStringList args = app.arguments();
//    args.removeFirst();
    watcher.addPaths(args);

    viewer.append("Watching files:" + watcher.files().join(";"));
    viewer.append("Watching directories:" + watcher.directories().join(";"));

    QObject::connect(&watcher, SIGNAL(fileChanged(QString)), &viewer, SLOT(slotFileChanged(QString)));
    QObject::connect(&watcher, SIGNAL(directoryChanged(QString)), &viewer, SLOT(slotDirChanged(QString)));

    viewer.show();

    return app.exec();
}


