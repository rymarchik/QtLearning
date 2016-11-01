/********************************************************************************
** Form generated from reading UI file 'dlgdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGDIALOG_H
#define UI_DLGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEditTermhierarchy;
    QLabel *labelTermshortname;
    QLabel *labelTermname;
    QLineEdit *lineEditTermname;
    QLabel *labelTermhierarchy;
    QLineEdit *lineEditTermshortname;

    void setupUi(QDialog *dlgDialog)
    {
        if (dlgDialog->objectName().isEmpty())
            dlgDialog->setObjectName(QStringLiteral("dlgDialog"));
        dlgDialog->setWindowModality(Qt::ApplicationModal);
        dlgDialog->resize(474, 140);
        buttonBox = new QDialogButtonBox(dlgDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(120, 100, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(dlgDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 10, 471, 94));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        gridLayout->setContentsMargins(10, 0, 10, 0);
        lineEditTermhierarchy = new QLineEdit(layoutWidget);
        lineEditTermhierarchy->setObjectName(QStringLiteral("lineEditTermhierarchy"));

        gridLayout->addWidget(lineEditTermhierarchy, 1, 1, 1, 1);

        labelTermshortname = new QLabel(layoutWidget);
        labelTermshortname->setObjectName(QStringLiteral("labelTermshortname"));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        labelTermshortname->setFont(font);

        gridLayout->addWidget(labelTermshortname, 2, 0, 1, 1);

        labelTermname = new QLabel(layoutWidget);
        labelTermname->setObjectName(QStringLiteral("labelTermname"));
        labelTermname->setFont(font);

        gridLayout->addWidget(labelTermname, 0, 0, 1, 1);

        lineEditTermname = new QLineEdit(layoutWidget);
        lineEditTermname->setObjectName(QStringLiteral("lineEditTermname"));
        lineEditTermname->setMouseTracking(false);
        lineEditTermname->setFocusPolicy(Qt::StrongFocus);
        lineEditTermname->setContextMenuPolicy(Qt::DefaultContextMenu);
        lineEditTermname->setCursorPosition(0);
        lineEditTermname->setCursorMoveStyle(Qt::VisualMoveStyle);

        gridLayout->addWidget(lineEditTermname, 0, 1, 1, 1);

        labelTermhierarchy = new QLabel(layoutWidget);
        labelTermhierarchy->setObjectName(QStringLiteral("labelTermhierarchy"));
        labelTermhierarchy->setFont(font);

        gridLayout->addWidget(labelTermhierarchy, 1, 0, 1, 1);

        lineEditTermshortname = new QLineEdit(layoutWidget);
        lineEditTermshortname->setObjectName(QStringLiteral("lineEditTermshortname"));

        gridLayout->addWidget(lineEditTermshortname, 2, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        labelTermshortname->setBuddy(lineEditTermshortname);
        labelTermname->setBuddy(lineEditTermname);
        labelTermhierarchy->setBuddy(lineEditTermhierarchy);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineEditTermname, lineEditTermhierarchy);
        QWidget::setTabOrder(lineEditTermhierarchy, lineEditTermshortname);

        retranslateUi(dlgDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), dlgDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dlgDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(dlgDialog);
    } // setupUi

    void retranslateUi(QDialog *dlgDialog)
    {
        dlgDialog->setWindowTitle(QApplication::translate("dlgDialog", "\320\244\320\276\321\200\320\274\320\260", 0));
        labelTermshortname->setText(QApplication::translate("dlgDialog", "\320\232\321\200\320\260\321\202\320\272\320\276\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", 0));
        labelTermname->setText(QApplication::translate("dlgDialog", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265 \320\277\320\276\320\275\321\217\321\202\320\270\321\217: ", 0));
        labelTermhierarchy->setText(QApplication::translate("dlgDialog", "\320\232\320\276\320\264 \320\277\320\276\320\275\321\217\321\202\320\270\321\217:", 0));
    } // retranslateUi

};

namespace Ui {
    class dlgDialog: public Ui_dlgDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGDIALOG_H
