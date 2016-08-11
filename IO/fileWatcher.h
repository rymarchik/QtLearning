#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QTextEdit>

class FileWatcher : public QTextEdit
{
    Q_OBJECT
public:
    explicit FileWatcher(QWidget *parent = 0);
public slots:
    void slotFileChanged(const QString&);
    void slotDirChanged(const QString&);
};

#endif // FILEWATCHER_H
