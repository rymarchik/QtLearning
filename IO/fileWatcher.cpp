#include "fileWatcher.h"

FileWatcher::FileWatcher(QWidget *parent) : QTextEdit(parent)
{
    setWindowTitle("File Watcher");
    setReadOnly(1);
}

void FileWatcher::slotFileChanged(const QString& str) {
    append("File changed" + str);
}

void FileWatcher::slotDirChanged(const QString &str) {
    append("Directory changed" + str);
}
