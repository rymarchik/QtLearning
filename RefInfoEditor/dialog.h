#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);

    void setLabelNames(QStringList);
    void setEmptyLineEdits(int);
    void placeFieldList(int);
    void fillFieldList(QStringList);

    void setMainComboBoxValues(QStringList);
    void setSecondComboBoxValues(QStringList);
    void setThirdComboBoxValues(QStringList);
    void setMainComboBoxCurrentIndex(int);

    int getMainComboBoxCurrentIndex();
    QString getCurrentMainComboBoxText();
    QString getCurrentSecondComboBoxText();
    QString getCurrentThirdComboBoxText();
    QString getCurrentFieldText(int);

    void clearLayout(QLayout*);
    void clearLineEdits(QLayout*);

    int getFieldsCount();
    void setLineEditValidator(int, QIntValidator);
    void setLineEditValidator(int, QDoubleValidator);

private:
    QComboBox* mainComboBox;
    QComboBox* comboBox2;
    QComboBox* comboBox3;

    QList<QLabel*>* labelList;
    QList<QLineEdit*>* fieldList;

    QVBoxLayout* labelLayout;
    QVBoxLayout* fieldLayout;

    QPushButton* okButton;
    QPushButton* cancelButton;

private slots:

};

#endif // DIALOG_H
