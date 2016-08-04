/********************************************************************************
** Form generated from reading UI file 'connectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTDIALOG_H
#define UI_CONNECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ConnectDialog
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QGroupBox *selectBackendBox;
    QGridLayout *gridLayout;
    QComboBox *backendListBox;
    QGroupBox *configurationBox;
    QGridLayout *gridLayout_4;
    QLabel *rawFilterLabel;
    QLineEdit *rawFilterEdit;
    QLabel *errorFilterLabel;
    QLineEdit *errorFilterEdit;
    QLabel *loopbackLabel;
    QComboBox *loopbackBox;
    QLabel *receiveOwnLabel;
    QComboBox *receiveOwnBox;
    QLabel *speedLabel;
    QComboBox *speedBox;
    QLabel *canFdLabel;
    QComboBox *canFdBox;
    QGroupBox *specifyInterfaceNameBox;
    QGridLayout *gridLayout_3;
    QLineEdit *interfaceNameEdit;
    QCheckBox *useConfigurationBox;

    void setupUi(QDialog *ConnectDialog)
    {
        if (ConnectDialog->objectName().isEmpty())
            ConnectDialog->setObjectName(QStringLiteral("ConnectDialog"));
        ConnectDialog->resize(441, 281);
        gridLayout_2 = new QGridLayout(ConnectDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(96, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(ConnectDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setAutoDefault(false);

        horizontalLayout->addWidget(cancelButton);

        okButton = new QPushButton(ConnectDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setAutoDefault(false);

        horizontalLayout->addWidget(okButton);


        gridLayout_2->addLayout(horizontalLayout, 4, 0, 1, 2);

        selectBackendBox = new QGroupBox(ConnectDialog);
        selectBackendBox->setObjectName(QStringLiteral("selectBackendBox"));
        gridLayout = new QGridLayout(selectBackendBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        backendListBox = new QComboBox(selectBackendBox);
        backendListBox->setObjectName(QStringLiteral("backendListBox"));

        gridLayout->addWidget(backendListBox, 0, 0, 1, 1);


        gridLayout_2->addWidget(selectBackendBox, 0, 0, 1, 1);

        configurationBox = new QGroupBox(ConnectDialog);
        configurationBox->setObjectName(QStringLiteral("configurationBox"));
        configurationBox->setEnabled(false);
        gridLayout_4 = new QGridLayout(configurationBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        rawFilterLabel = new QLabel(configurationBox);
        rawFilterLabel->setObjectName(QStringLiteral("rawFilterLabel"));

        gridLayout_4->addWidget(rawFilterLabel, 0, 0, 1, 1);

        rawFilterEdit = new QLineEdit(configurationBox);
        rawFilterEdit->setObjectName(QStringLiteral("rawFilterEdit"));
        rawFilterEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(rawFilterEdit, 0, 1, 1, 1);

        errorFilterLabel = new QLabel(configurationBox);
        errorFilterLabel->setObjectName(QStringLiteral("errorFilterLabel"));

        gridLayout_4->addWidget(errorFilterLabel, 1, 0, 1, 1);

        errorFilterEdit = new QLineEdit(configurationBox);
        errorFilterEdit->setObjectName(QStringLiteral("errorFilterEdit"));
        errorFilterEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(errorFilterEdit, 1, 1, 1, 1);

        loopbackLabel = new QLabel(configurationBox);
        loopbackLabel->setObjectName(QStringLiteral("loopbackLabel"));

        gridLayout_4->addWidget(loopbackLabel, 2, 0, 1, 1);

        loopbackBox = new QComboBox(configurationBox);
        loopbackBox->setObjectName(QStringLiteral("loopbackBox"));

        gridLayout_4->addWidget(loopbackBox, 2, 1, 1, 1);

        receiveOwnLabel = new QLabel(configurationBox);
        receiveOwnLabel->setObjectName(QStringLiteral("receiveOwnLabel"));

        gridLayout_4->addWidget(receiveOwnLabel, 3, 0, 1, 1);

        receiveOwnBox = new QComboBox(configurationBox);
        receiveOwnBox->setObjectName(QStringLiteral("receiveOwnBox"));

        gridLayout_4->addWidget(receiveOwnBox, 3, 1, 1, 1);

        speedLabel = new QLabel(configurationBox);
        speedLabel->setObjectName(QStringLiteral("speedLabel"));

        gridLayout_4->addWidget(speedLabel, 4, 0, 1, 1);

        speedBox = new QComboBox(configurationBox);
        speedBox->setObjectName(QStringLiteral("speedBox"));

        gridLayout_4->addWidget(speedBox, 4, 1, 1, 1);

        canFdLabel = new QLabel(configurationBox);
        canFdLabel->setObjectName(QStringLiteral("canFdLabel"));

        gridLayout_4->addWidget(canFdLabel, 5, 0, 1, 1);

        canFdBox = new QComboBox(configurationBox);
        canFdBox->setObjectName(QStringLiteral("canFdBox"));

        gridLayout_4->addWidget(canFdBox, 5, 1, 1, 1);


        gridLayout_2->addWidget(configurationBox, 0, 1, 4, 1);

        specifyInterfaceNameBox = new QGroupBox(ConnectDialog);
        specifyInterfaceNameBox->setObjectName(QStringLiteral("specifyInterfaceNameBox"));
        gridLayout_3 = new QGridLayout(specifyInterfaceNameBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        interfaceNameEdit = new QLineEdit(specifyInterfaceNameBox);
        interfaceNameEdit->setObjectName(QStringLiteral("interfaceNameEdit"));

        gridLayout_3->addWidget(interfaceNameEdit, 0, 0, 1, 1);


        gridLayout_2->addWidget(specifyInterfaceNameBox, 1, 0, 1, 1);

        useConfigurationBox = new QCheckBox(ConnectDialog);
        useConfigurationBox->setObjectName(QStringLiteral("useConfigurationBox"));

        gridLayout_2->addWidget(useConfigurationBox, 3, 0, 1, 1);


        retranslateUi(ConnectDialog);

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(ConnectDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectDialog)
    {
        ConnectDialog->setWindowTitle(QApplication::translate("ConnectDialog", "Connect", 0));
        cancelButton->setText(QApplication::translate("ConnectDialog", "Cancel", 0));
        okButton->setText(QApplication::translate("ConnectDialog", "OK", 0));
        selectBackendBox->setTitle(QApplication::translate("ConnectDialog", "Select CAN backend", 0));
        configurationBox->setTitle(QApplication::translate("ConnectDialog", "Specify Configuration", 0));
        rawFilterLabel->setText(QApplication::translate("ConnectDialog", "RAW Filter", 0));
        errorFilterLabel->setText(QApplication::translate("ConnectDialog", "Error Filter", 0));
        errorFilterEdit->setPlaceholderText(QApplication::translate("ConnectDialog", "FrameError bits", 0));
        loopbackLabel->setText(QApplication::translate("ConnectDialog", "Loopback", 0));
        receiveOwnLabel->setText(QApplication::translate("ConnectDialog", "Receive Own", 0));
        speedLabel->setText(QApplication::translate("ConnectDialog", "Speed", 0));
        canFdLabel->setText(QApplication::translate("ConnectDialog", "CAN FD", 0));
        specifyInterfaceNameBox->setTitle(QApplication::translate("ConnectDialog", "Specify CAN interface name", 0));
        useConfigurationBox->setText(QApplication::translate("ConnectDialog", "Custom configuration", 0));
    } // retranslateUi

};

namespace Ui {
    class ConnectDialog: public Ui_ConnectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTDIALOG_H
