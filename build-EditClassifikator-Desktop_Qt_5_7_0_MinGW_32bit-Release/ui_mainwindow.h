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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *m_Find;
    QAction *m_Add;
    QAction *m_Delete;
    QAction *m_Save;
    QAction *m_Refresh;
    QAction *m_Edit;
    QAction *m_Exit;
    QAction *m_Import;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(915, 580);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/EditClassifikator/Resources/AddressBook.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        m_Find = new QAction(MainWindow);
        m_Find->setObjectName(QStringLiteral("m_Find"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/EditClassifikator/Resources/8.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_Find->setIcon(icon1);
        m_Add = new QAction(MainWindow);
        m_Add->setObjectName(QStringLiteral("m_Add"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/EditClassifikator/Resources/document (2).png"), QSize(), QIcon::Normal, QIcon::Off);
        m_Add->setIcon(icon2);
        m_Delete = new QAction(MainWindow);
        m_Delete->setObjectName(QStringLiteral("m_Delete"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/EditClassifikator/Resources/document (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        m_Delete->setIcon(icon3);
        m_Save = new QAction(MainWindow);
        m_Save->setObjectName(QStringLiteral("m_Save"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/EditClassifikator/Resources/documentsave.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_Save->setIcon(icon4);
        m_Refresh = new QAction(MainWindow);
        m_Refresh->setObjectName(QStringLiteral("m_Refresh"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/EditClassifikator/Resources/refresh (3).png"), QSize(), QIcon::Normal, QIcon::Off);
        m_Refresh->setIcon(icon5);
        m_Edit = new QAction(MainWindow);
        m_Edit->setObjectName(QStringLiteral("m_Edit"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/EditClassifikator/Resources/documentedit.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_Edit->setIcon(icon6);
        m_Exit = new QAction(MainWindow);
        m_Exit->setObjectName(QStringLiteral("m_Exit"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/EditClassifikator/Resources/out.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_Exit->setIcon(icon7);
        m_Import = new QAction(MainWindow);
        m_Import->setObjectName(QStringLiteral("m_Import"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/EditClassifikator/Resources/oldgobottom.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_Import->setIcon(icon8);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(915, 472));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeWidget = new QTreeWidget(centralWidget);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferDefault);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        font2.setKerning(false);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(2, font2);
        __qtreewidgetitem->setTextAlignment(1, Qt::AlignJustify|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(1, font1);
        __qtreewidgetitem->setForeground(1, brush);
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(0, font);
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setEnabled(true);
        treeWidget->setMaximumSize(QSize(16777000, 16777000));
        QFont font3;
        font3.setPointSize(11);
        treeWidget->setFont(font3);
        treeWidget->setAcceptDrops(false);
        treeWidget->setLayoutDirection(Qt::LeftToRight);
        treeWidget->setAutoFillBackground(true);
        treeWidget->setInputMethodHints(Qt::ImhNone);
        treeWidget->setFrameShape(QFrame::NoFrame);
        treeWidget->setFrameShadow(QFrame::Sunken);
        treeWidget->setLineWidth(3);
        treeWidget->setMidLineWidth(0);
        treeWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        treeWidget->setProperty("showDropIndicator", QVariant(true));
        treeWidget->setAlternatingRowColors(true);
        treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeWidget->setIconSize(QSize(10, 10));
        treeWidget->setTextElideMode(Qt::ElideMiddle);
        treeWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        treeWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        treeWidget->setAutoExpandDelay(1);
        treeWidget->setIndentation(40);
        treeWidget->setRootIsDecorated(true);
        treeWidget->setUniformRowHeights(false);
        treeWidget->setItemsExpandable(true);
        treeWidget->setSortingEnabled(true);
        treeWidget->setAnimated(false);
        treeWidget->setAllColumnsShowFocus(true);
        treeWidget->setWordWrap(false);
        treeWidget->setHeaderHidden(false);
        treeWidget->setColumnCount(3);
        treeWidget->header()->setVisible(false);
        treeWidget->header()->setCascadingSectionResizes(true);
        treeWidget->header()->setHighlightSections(false);
        treeWidget->header()->setMinimumSectionSize(100);
        treeWidget->header()->setProperty("showSortIndicator", QVariant(true));
        treeWidget->header()->setStretchLastSection(true);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setLayoutDirection(Qt::LeftToRight);
        mainToolBar->setMovable(true);
        mainToolBar->setAllowedAreas(Qt::AllToolBarAreas);
        mainToolBar->setOrientation(Qt::Horizontal);
        mainToolBar->setIconSize(QSize(40, 40));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addSeparator();
        mainToolBar->addAction(m_Add);
        mainToolBar->addAction(m_Edit);
        mainToolBar->addAction(m_Delete);
        mainToolBar->addSeparator();
        mainToolBar->addAction(m_Save);
        mainToolBar->addSeparator();
        mainToolBar->addAction(m_Find);
        mainToolBar->addSeparator();
        mainToolBar->addAction(m_Import);
        mainToolBar->addSeparator();
        mainToolBar->addAction(m_Refresh);
        mainToolBar->addAction(m_Exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\232\320\273\320\260\321\201\321\201\320\270\321\204\320\270\320\272\320\260\321\202\320\276\321\200", 0));
        m_Find->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", 0));
        m_Add->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
#ifndef QT_NO_TOOLTIP
        m_Add->setToolTip(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
#endif // QT_NO_TOOLTIP
        m_Delete->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        m_Save->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        m_Refresh->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", 0));
        m_Edit->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", 0));
#ifndef QT_NO_TOOLTIP
        m_Edit->setToolTip(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", 0));
#endif // QT_NO_TOOLTIP
        m_Exit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
#ifndef QT_NO_TOOLTIP
        m_Exit->setToolTip(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
#endif // QT_NO_TOOLTIP
        m_Import->setText(QApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202", 0));
#ifndef QT_NO_TOOLTIP
        m_Import->setToolTip(QApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202", 0));
#endif // QT_NO_TOOLTIP
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "3", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "2", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "1", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
