#include "dialog.h"
#include "editor.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent, Qt::WindowCloseButtonHint)
{
    mainComboBox = new QComboBox;
    comboBox2 = new QComboBox;
    comboBox2->setObjectName("secondCB");
    comboBox3 = new QComboBox;

    labelList = new QList<QLabel*>;
    fieldList = new QList<QLineEdit*>;

    okButton = new QPushButton("Принять");
    cancelButton = new QPushButton("Отменить");

    labelLayout = new QVBoxLayout;
    fieldLayout = new QVBoxLayout;

    QHBoxLayout* infoLayout = new QHBoxLayout;
    infoLayout->addLayout(labelLayout);
    infoLayout->addLayout(fieldLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(mainComboBox, SIGNAL(currentIndexChanged(int)), this->parent(), SLOT(slotChangeRootItemValue(int)));
    connect(comboBox2, SIGNAL(currentIndexChanged(int)), this->parent(), SLOT(slotChange2ndRootItemValue(int)));
    connect(comboBox3, SIGNAL(currentIndexChanged(int)), this->parent(), SLOT(slotChange3rdRootItemValue(int)));
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
    }
}

void Dialog::setMainComboBoxValues(QStringList list) {
    mainComboBox->setHidden(false);
    comboBox2->setHidden(true);
    comboBox3->setHidden(true);
    mainComboBox->clear();

    mainComboBox->addItems(list);
    fieldLayout->insertWidget(0, mainComboBox);
}

void Dialog::setSecondComboBoxValues(QStringList list) {
    comboBox2->setHidden(false);
    comboBox2->clear();
    comboBox2->addItems(list);

    int comboBoxOverseer = 0;
    for (int i = 0; i < fieldLayout->count(); i++) {
        if (fieldLayout->itemAt(i)->widget()->objectName() == "secondCB") {
            comboBoxOverseer++;
            return;
        }
    }

    if (comboBoxOverseer == 0) {
        fieldLayout->insertWidget(0, comboBox2);
    }
}

void Dialog::setThirdComboBoxValues(QStringList list) {
    comboBox3->setHidden(false);
    comboBox3->clear();
    comboBox3->addItems(list);

    if (fieldLayout->count() < 4) {
        fieldLayout->insertWidget(0, comboBox3);
    }
}

void Dialog::setEmptyLineEdits(int n) {
    clearLineEdits(fieldLayout);
    mainComboBox->setHidden(true);
    comboBox2->setHidden(true);
    comboBox3->setHidden(true);
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
    mainComboBox->setCurrentIndex(index);
}

QString Dialog::getCurrentMainComboBoxText() {
    return mainComboBox->currentText();
}

QString Dialog::getCurrentSecondComboBoxText() {
    return comboBox2->currentText();
}

QString Dialog::getCurrentThirdComboBoxText() {
    return comboBox3->currentText();
}

QString Dialog::getCurrentFieldText(int n) {
    return fieldList->at(n)->text();
}
