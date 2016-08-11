#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QtWidgets>

class FileFinder : public QWidget
{
    Q_OBJECT
public:
    explicit FileFinder(QWidget *parent = 0);
    void start(const QDir& dir);
private:
    QLabel* pathLabel;
    QLabel* extLabel;
    QLineEdit* pathField;
    QLineEdit* extField;
    QPushButton* browseButton;
    QPushButton* findButton;
    QTextEdit* result;
public slots:
    void slotBrowse();
    void slotFind();
};

#endif // DIRECTORY_H
