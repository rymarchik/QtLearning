#include "fileFinder.h"

FileFinder::FileFinder(QWidget *parent) : QWidget(parent)
{
    pathField = new QLineEdit(QDir::current().absolutePath());
    extField = new QLineEdit("*.cpp *.h");
    result = new QTextEdit;
    result->setReadOnly(true);

    pathLabel = new QLabel("Directory");
    extLabel = new QLabel("Extension");
    browseButton = new QPushButton(QPixmap(":/fileopen.png"), "");
    findButton = new QPushButton("Find");

    connect(browseButton, SIGNAL(clicked()), SLOT(slotBrowse()));
    connect(findButton, SIGNAL(clicked()), SLOT(slotFind()));

    QGridLayout* grid = new QGridLayout;
    grid->addWidget(pathLabel, 0, 0);
    grid->addWidget(extLabel, 1, 0);
    grid->addWidget(pathField, 0, 1);
    grid->addWidget(extField, 1, 1);
    grid->addWidget(browseButton, 0, 2);
    grid->addWidget(findButton, 1, 2);
    grid->addWidget(result, 2, 0, 1, 3);
    grid->setMargin(10);
    grid->setSpacing(15);
    setLayout(grid);
    resize(500, 300);
}

void FileFinder::slotBrowse() {
    QString str = QFileDialog::getExistingDirectory(0, "Select a directory", pathField->text());
    if (!str.isEmpty()) {
        pathField->setText(str);
    }
}

void FileFinder::slotFind() {
    start(QDir(pathField->text()));
}

void FileFinder::start(const QDir &dir) {
    QApplication::processEvents();
    QStringList listFiles = dir.entryList(extField->text().split(" "), QDir::Files);

    foreach (QString file, listFiles) {
        result->append(dir.absoluteFilePath(file));
    }

    QStringList listDirs = dir.entryList(QDir::Dirs);

    foreach (QString subdir, listDirs) {
        if (subdir == "." || subdir == "..") {
            continue;
        }
        start(QDir(dir.absoluteFilePath(subdir)));
    }
}
