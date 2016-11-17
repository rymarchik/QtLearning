#include "dialog.h"
#include "editor.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent, Qt::WindowCloseButtonHint)
{
    editRootItem = new QComboBox;

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
    connect(editRootItem, SIGNAL(currentIndexChanged(int)), this->parent(), SLOT(slotChangeRootItemValue(int)));

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

void Dialog::clearLayoutExceptFirst(QLayout* layout) {
    while (QLayoutItem* item = layout->takeAt(1))
    {
        if (QWidget* widget = item->widget())
            delete widget;
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout);
        delete item;
    }
}

void Dialog::setHeaderNames(QStringList list) {
    clearLayout(labelLayout);
    labelList->clear();

    for (int i = 0; i < list.size(); i++) {
        labelList->append(new QLabel(list.at(i)));
        labelLayout->addWidget(labelList->last());
    }
}

void Dialog::setRootItemValues(QStringList list) {
    if (editRootItem->count() == 0)
        clearLayout(fieldLayout);
    editRootItem->setHidden(false);
    editRootItem->clear();

    editRootItem->addItems(list);
    fieldLayout->insertWidget(0, editRootItem);
}

void Dialog::setEmptyLineEdits(int n) {
    if (editRootItem->count() == 0)
        clearLayout(fieldLayout);
    else
        clearLayoutExceptFirst(fieldLayout);
    editRootItem->setHidden(true);
    fieldList->clear();

    for (int i = 0; i < n; i++) {
        fieldList->append(new QLineEdit);
        fieldLayout->addWidget(fieldList->at(i));
    }
}

void Dialog::setLineEdits(int n) {
    clearLayoutExceptFirst(fieldLayout);

    for (int i = 0; i < n; i++) {
        fieldLayout->addWidget(fieldList->at(i));
    }
}

void Dialog::setItemValues(QStringList list) {
    fieldList->clear();

    for (int i = 0; i < list.size(); i++) {
        fieldList->append(new QLineEdit(list.at(i)));
    }
}
