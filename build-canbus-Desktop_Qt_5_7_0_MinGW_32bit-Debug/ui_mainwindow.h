/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionQuit;
    QAction *actionAboutQt;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGroupBox *sendMessagesBox;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *idEdit;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *dataFrame;
    QRadioButton *remoteFrame;
    QRadioButton *errorFrame;
    QCheckBox *fdBox;
    QCheckBox *effBox;
    QPushButton *sendButton;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QListWidget *receiveList;
    QListWidget *requestList;
    QListWidget *errorList;
    QMenuBar *menuBar;
    QMenu *menuCalls;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(551, 481);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon2);
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        sendMessagesBox = new QGroupBox(centralWidget);
        sendMessagesBox->setObjectName(QStringLiteral("sendMessagesBox"));
        horizontalLayout = new QHBoxLayout(sendMessagesBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(sendMessagesBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        idEdit = new QLineEdit(sendMessagesBox);
        idEdit->setObjectName(QStringLiteral("idEdit"));

        gridLayout->addWidget(idEdit, 0, 1, 1, 1);

        groupBox = new QGroupBox(sendMessagesBox);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setCheckable(false);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        dataFrame = new QRadioButton(groupBox);
        dataFrame->setObjectName(QStringLiteral("dataFrame"));
        dataFrame->setChecked(true);

        verticalLayout->addWidget(dataFrame);

        remoteFrame = new QRadioButton(groupBox);
        remoteFrame->setObjectName(QStringLiteral("remoteFrame"));

        verticalLayout->addWidget(remoteFrame);

        errorFrame = new QRadioButton(groupBox);
        errorFrame->setObjectName(QStringLiteral("errorFrame"));

        verticalLayout->addWidget(errorFrame);


        gridLayout->addWidget(groupBox, 0, 2, 3, 1);

        fdBox = new QCheckBox(sendMessagesBox);
        fdBox->setObjectName(QStringLiteral("fdBox"));

        gridLayout->addWidget(fdBox, 0, 3, 1, 1);

        effBox = new QCheckBox(sendMessagesBox);
        effBox->setObjectName(QStringLiteral("effBox"));

        gridLayout->addWidget(effBox, 1, 3, 1, 1);

        sendButton = new QPushButton(sendMessagesBox);
        sendButton->setObjectName(QStringLiteral("sendButton"));

        gridLayout->addWidget(sendButton, 2, 3, 1, 1);

        lineEdit = new QLineEdit(sendMessagesBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        label_2 = new QLabel(sendMessagesBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        gridLayout_3->addWidget(sendMessagesBox, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 0, 1, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 0, 2, 1, 1);

        receiveList = new QListWidget(centralWidget);
        receiveList->setObjectName(QStringLiteral("receiveList"));

        gridLayout_2->addWidget(receiveList, 1, 0, 1, 1);

        requestList = new QListWidget(centralWidget);
        requestList->setObjectName(QStringLiteral("requestList"));

        gridLayout_2->addWidget(requestList, 1, 1, 1, 1);

        errorList = new QListWidget(centralWidget);
        errorList->setObjectName(QStringLiteral("errorList"));

        gridLayout_2->addWidget(errorList, 1, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 551, 25));
        menuCalls = new QMenu(menuBar);
        menuCalls->setObjectName(QStringLiteral("menuCalls"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCalls->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuCalls->addAction(actionConnect);
        menuCalls->addAction(actionDisconnect);
        menuCalls->addSeparator();
        menuCalls->addAction(actionQuit);
        menuHelp->addAction(actionAboutQt);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CAN Example", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "&Connect", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "&Disconnect", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0));
        actionAboutQt->setText(QApplication::translate("MainWindow", "&About Qt", 0));
        sendMessagesBox->setTitle(QApplication::translate("MainWindow", "Send CAN message", 0));
        label->setText(QApplication::translate("MainWindow", "ID (hex)", 0));
        idEdit->setPlaceholderText(QApplication::translate("MainWindow", "123", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Frame Type", 0));
        dataFrame->setText(QApplication::translate("MainWindow", "Data", 0));
        remoteFrame->setText(QApplication::translate("MainWindow", "Re&mote Request", 0));
        errorFrame->setText(QApplication::translate("MainWindow", "Error", 0));
        fdBox->setText(QApplication::translate("MainWindow", "Flexible Data-Rate\n"
"(64 byte payload)", 0));
#ifndef QT_NO_TOOLTIP
        effBox->setToolTip(QApplication::translate("MainWindow", "Allow extended frames with 29 bit identifier.\n"
"Otherwise, the standard format with 11 bit idenfier is used.", 0));
#endif // QT_NO_TOOLTIP
        effBox->setText(QApplication::translate("MainWindow", "Extended Frame\n"
"(29 bit identifier)", 0));
        sendButton->setText(QApplication::translate("MainWindow", "send", 0));
        lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "12 34 AB CE", 0));
        label_2->setText(QApplication::translate("MainWindow", "Data (hex)", 0));
        label_4->setText(QApplication::translate("MainWindow", "Messages", 0));
        label_5->setText(QApplication::translate("MainWindow", "Requests", 0));
        label_6->setText(QApplication::translate("MainWindow", "Errors", 0));
        menuCalls->setTitle(QApplication::translate("MainWindow", "&Calls", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
