#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);

    void setHeaderNames(QStringList);
    void setRootItemValues(QStringList);
    void setItemValues(QStringList);

private:
    QLineEdit* newRootItem;
    QComboBox* editRootItem;

    QList<QLabel*>* labelList;
    QList<QLineEdit*>* fieldList;

    QPushButton* okButton;
    QPushButton* cancelButton;

    QGridLayout* infoLayout;

private slots:

};

#endif // DIALOG_H
