/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QStringLiteral("widget"));
        widget->resize(400, 300);
        menuBar = new QMenuBar(widget);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        widget->setMenuBar(menuBar);
        mainToolBar = new QToolBar(widget);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        widget->addToolBar(mainToolBar);
        centralWidget = new QWidget(widget);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(widget);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        widget->setStatusBar(statusBar);

        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QMainWindow *widget)
    {
        widget->setWindowTitle(QApplication::translate("widget", "widget", 0));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
