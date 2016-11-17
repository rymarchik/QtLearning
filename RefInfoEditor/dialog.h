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
    void setEmptyLineEdits(int);
    void setLineEdits(int);
    void setItemValues(QStringList);

    void clearLayout(QLayout*);
    void clearLayoutExceptFirst(QLayout*);

private:
    QLineEdit* newRootItem;
    QComboBox* editRootItem;

    QList<QLabel*>* labelList;
    QList<QLineEdit*>* fieldList;

    QVBoxLayout* labelLayout;
    QVBoxLayout* fieldLayout;

    QPushButton* okButton;
    QPushButton* cancelButton;

private slots:

};

#endif // DIALOG_H
