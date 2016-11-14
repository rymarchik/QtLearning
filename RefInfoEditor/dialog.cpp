#include "dialog.h"
#include "editor.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent, Qt::WindowCloseButtonHint)
{
    editRootItem = new QComboBox;

//    editRootItem->setHidden();

    labelList = new QList<QLabel*>;
    fieldList = new QList<QLineEdit*>;

    okButton = new QPushButton("Принять");
    cancelButton = new QPushButton("Отменить");

    infoLayout = new QGridLayout;
    infoLayout->addWidget(editRootItem, 0, 1);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));

}

void Dialog::setHeaderNames(QStringList list) {
    for (int i = 0; i < list.size(); i++) {
        labelList->append(new QLabel(list.at(i)));
        infoLayout->addWidget(labelList->at(i), i, 0);
    }
}

void Dialog::setRootItemValues(QStringList list) {
    editRootItem->insertItems(0, list);
}

void Dialog::setItemValues(QStringList list) {
    for (int i = 0; i < list.size(); i++) {
        fieldList->append(new QLineEdit(list.at(i)));
        infoLayout->addWidget(fieldList->at(i), i + 1, 1);
    }
}
