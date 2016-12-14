#include "dialog.h"
#include "editor.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent, Qt::WindowCloseButtonHint)
{
    addDialComboBox1 = new QComboBox;
    addDialComboBox2 = new QComboBox;
    addDialComboBox2->setObjectName("addSecondCB");
    addDialComboBox3 = new QComboBox;
    addDialComboBox3->setObjectName("addThirdCB");
    editDialComboBox1 = new QComboBox;
    editDialComboBox2 = new QComboBox;
    editDialComboBox2->setObjectName("editSecondCB");
    editDialComboBox3 = new QComboBox;
    editDialComboBox3->setObjectName("editThirdCB");

    labelList = new QList<QLabel*>;
    fieldList = new QList<QLineEdit*>;

    okButton = new QPushButton("Принять");
    cancelButton = new QPushButton("Отменить");

    labelLayout = new QVBoxLayout;
    labelLayout->setContentsMargins(0, 10, 15, 0);
    fieldLayout = new QVBoxLayout;

    QHBoxLayout* infoLayout = new QHBoxLayout;
    infoLayout->addLayout(labelLayout);
    infoLayout->addLayout(fieldLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->setSpacing(33);
    buttonLayout->setContentsMargins(0, 10, 0, 0);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setContentsMargins(25, 10, 25, 15);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(addDialComboBox1, SIGNAL(currentIndexChanged(int)), this->parent(), SLOT(slotAddDialChangeComboBox1(int)));
    connect(addDialComboBox2, SIGNAL(currentIndexChanged(int)), this->parent(), SLOT(slotAddDialChangeComboBox2(int)));
    connect(editDialComboBox1, SIGNAL(currentIndexChanged(int)), this->parent(), SLOT(slotEditDialChangeComboBox1(int)));
    connect(editDialComboBox2, SIGNAL(currentIndexChanged(int)), this->parent(), SLOT(slotEditDialChangeComboBox2(int)));
    connect(editDialComboBox3, SIGNAL(currentIndexChanged(int)), this->parent(), SLOT(slotEditDialChangeComboBox3(int)));
}

void Dialog::clearLayout(QLayout* layout) {
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (QWidget* widget = item->widget())
            delete widget;
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout);
        delete item;
    }
}

void Dialog::clearLineEdits(QLayout* layout) {
    int wgtCount = layout->count();
    qDebug() << "before = " << wgtCount;
    for (int i = wgtCount - 1; i >= 0; i--) {
        qDebug() << i;
        if (layout->itemAt(i)->widget()->metaObject()->className() == QString("QLineEdit")) {
            delete layout->takeAt(i)->widget();
            delete layout->takeAt(i);
            qDebug() << i;
        }
    }
    qDebug() << "after = " << layout->count();
}

void Dialog::setLabelNames(QStringList list) {
    clearLayout(labelLayout);
    labelList->clear();

    for (int i = 0; i < list.size(); i++) {
        labelList->append(new QLabel(list.at(i)));
        labelLayout->addWidget(labelList->last());
        if (!list.at(i).contains("\n")) {
            labelLayout->addSpacing(12);
        }
    }
}

void Dialog::setAddDialComboBox1Values(QStringList list) {
    addDialComboBox1->setHidden(false);
    addDialComboBox1->clear();

    addDialComboBox1->addItems(list);
    fieldLayout->insertWidget(0, addDialComboBox1);
}

void Dialog::setAddDialComboBox2Values(QStringList list) {
    addDialComboBox2->setHidden(false);
    addDialComboBox2->clear();
    addDialComboBox2->addItems(list);

    int comboBoxOverseer = 0;
    for (int i = 0; i < fieldLayout->count(); i++) {
        if (fieldLayout->itemAt(i)->widget()->objectName() == "addSecondCB") {
            comboBoxOverseer++;
            return;
        }
    }
    if (comboBoxOverseer == 0) {
        fieldLayout->insertWidget(0, addDialComboBox2);
    }
}

void Dialog::setAddDialComboBox3Values(QStringList list) {
    addDialComboBox3->setHidden(false);
    addDialComboBox3->clear();
    addDialComboBox3->addItems(list);

    int comboBoxOverseer = 0;
    for (int i = 0; i < fieldLayout->count(); i++) {
        if (fieldLayout->itemAt(i)->widget()->objectName() == "addThirdCB") {
            comboBoxOverseer++;
            return;
        }
    }
    if (comboBoxOverseer == 0) {
        fieldLayout->insertWidget(0, addDialComboBox3);
    }
}

void Dialog::setEditDialComboBox1Values(QStringList list) {
    addDialComboBox1->setHidden(true);
    addDialComboBox2->setHidden(true);
    addDialComboBox3->setHidden(true);
    editDialComboBox1->setHidden(false);
    editDialComboBox2->setHidden(true);
    editDialComboBox3->setHidden(true);
    editDialComboBox1->clear();

    editDialComboBox1->addItems(list);
    fieldLayout->insertWidget(0, editDialComboBox1);
}

void Dialog::setEditDialComboBox2Values(QStringList list) {
    editDialComboBox2->setHidden(false);
    editDialComboBox2->clear();
    editDialComboBox2->addItems(list);

    int comboBoxOverseer = 0;
    for (int i = 0; i < fieldLayout->count(); i++) {
        if (fieldLayout->itemAt(i)->widget()->objectName() == "editSecondCB") {
            comboBoxOverseer++;
            return;
        }
    }
    if (comboBoxOverseer == 0) {
        fieldLayout->insertWidget(0, editDialComboBox2);
    }
}

void Dialog::setEditDialComboBox3Values(QStringList list) {
    editDialComboBox3->setHidden(false);
    editDialComboBox3->clear();
    editDialComboBox3->addItems(list);

    int comboBoxOverseer = 0;
    for (int i = 0; i < fieldLayout->count(); i++) {
        if (fieldLayout->itemAt(i)->widget()->objectName() == "editThirdCB") {
            comboBoxOverseer++;
            return;
        }
    }
    if (comboBoxOverseer == 0) {
        fieldLayout->insertWidget(0, editDialComboBox3);
    }
}

void Dialog::setEmptyLineEdits(int n) {
    clearLineEdits(fieldLayout);
    addDialComboBox1->setHidden(true);
    addDialComboBox2->setHidden(true);
    addDialComboBox3->setHidden(true);
    editDialComboBox1->setHidden(true);
    editDialComboBox2->setHidden(true);
    editDialComboBox3->setHidden(true);
    fieldList->clear();

    for (int i = 0; i < n; i++) {
        fieldList->append(new QLineEdit);
        fieldLayout->addWidget(fieldList->at(i));
    }
}

void Dialog::placeFieldList(int n) {
    clearLineEdits(fieldLayout);

    for (int i = 0; i < n; i++) {
        fieldLayout->addWidget(fieldList->at(i));
    }
}

void Dialog::fillFieldList(QStringList list) {
    fieldList->clear();

    for (int i = 0; i < list.size(); i++) {
        fieldList->append(new QLineEdit(list.at(i)));
    }
}

void Dialog::setMainComboBoxCurrentIndex(int index) {
    editDialComboBox1->setCurrentIndex(index);
}

void Dialog::setMainComboBoxCurrentText(QString str) {
    editDialComboBox1->setCurrentText(str);
}

void Dialog::setSecondComboBoxCurrentText(QString str) {
    editDialComboBox2->setCurrentText(str);
}

void Dialog::setThirdComboBoxCurrentText(QString str) {
    editDialComboBox3->setCurrentText(str);
}


int Dialog::getMainComboBoxCurrentIndex() {
    return editDialComboBox1->currentIndex();
}

QString Dialog::getCurrentMainComboBoxText() {
    return editDialComboBox1->currentText();
}

QString Dialog::getCurrentSecondComboBoxText() {
    return editDialComboBox2->currentText();
}

QString Dialog::getCurrentThirdComboBoxText() {
    return editDialComboBox3->currentText();
}


int Dialog::getCurrentAddDialCB1Index() {
    return addDialComboBox1->currentIndex();
}

QString Dialog::getCurrentAddDialCB1Text() {
    return addDialComboBox1->currentText();
}

QString Dialog::getCurrentAddDialCB2Text() {
    return addDialComboBox2->currentText();
}

QString Dialog::getCurrentAddDialCB3Text() {
    return addDialComboBox3->currentText();
}

void Dialog::setCurrentAddDialCB1Index(int index) {
    addDialComboBox1->setCurrentIndex(index);
}


QString Dialog::getCurrentFieldText(int n) {
    return fieldList->at(n)->text();
}

int Dialog::getFieldsCount() {
    return fieldList->size();
}

void Dialog::setLineEditValidator(int index, QIntValidator* validator) {
    fieldList->at(index)->setValidator(validator);
}

void Dialog::setLineEditValidator(int index, QDoubleValidator* validator) {
    fieldList->at(index)->setValidator(validator);
}

void Dialog::setLineEditPlaceholder(int index, QString str) {
    fieldList->at(index)->setPlaceholderText(str);
}

QString Dialog::copyToQString(WCHAR array[MAX_PATH]) {
    QString string;
    int i = 0;
    while (array[i] != 0)
    {
        string[i] = array[i];
        i++;
    }
    return string;
}

void Dialog::openKeyboard() {
    process->start(virtualKeyboard);
}

void Dialog::closeKeyboard() {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 proc = { sizeof(proc) };
    if (Process32First(hSnap, &proc))
    {
        while (Process32Next(hSnap, &proc))
        {
            QString fileName = copyToQString(proc.szExeFile);
            if(fileName == QString("osk.exe"))
            {
                HANDLE hp = OpenProcess(1, false, proc.th32ProcessID );
                TerminateProcess(hp, 0);
            }
        }
    }
}
