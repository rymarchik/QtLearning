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

    void setAddDialComboBox1Values(QStringList);
    void setAddDialComboBox2Values(QStringList);
    void setAddDialComboBox3Values(QStringList);
    void setEditDialComboBox1Values(QStringList);
    void setEditDialComboBox2Values(QStringList);
    void setEditDialComboBox3Values(QStringList);

    void setMainComboBoxCurrentIndex(int);
    void setMainComboBoxCurrentText(QString);
    void setSecondComboBoxCurrentText(QString);
    void setThirdComboBoxCurrentText(QString);

    int getMainComboBoxCurrentIndex();
    QString getCurrentMainComboBoxText();
    QString getCurrentSecondComboBoxText();
    QString getCurrentThirdComboBoxText();
    QString getCurrentFieldText(int);

    int getCurrentAddDialCB1Index();
    QString getCurrentAddDialCB1Text();
    QString getCurrentAddDialCB2Text();
    QString getCurrentAddDialCB3Text();
    void setCurrentAddDialCB1Index(int);

    void clearLayout(QLayout*);
    void clearLineEdits(QLayout*);

    int getFieldsCount();
    void setLineEditValidator(int, QIntValidator*);
    void setLineEditValidator(int, QDoubleValidator*);
    void setLineEditPlaceholder(int, QString);

private:
    QComboBox* addDialComboBox1;
    QComboBox* addDialComboBox2;
    QComboBox* addDialComboBox3;
    QComboBox* editDialComboBox1;
    QComboBox* editDialComboBox2;
    QComboBox* editDialComboBox3;

    QList<QLabel*>* labelList;
    QList<QLineEdit*>* fieldList;

    QVBoxLayout* labelLayout;
    QVBoxLayout* fieldLayout;

    QPushButton* okButton;
    QPushButton* cancelButton;

protected:

private slots:
};

#endif // DIALOG_H
