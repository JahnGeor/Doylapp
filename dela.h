#ifndef DELA_H
#define DELA_H

#include <QDialog>
#include "popup.h"

namespace Ui {
class DelA;
}

class DelA : public QDialog
{
    Q_OBJECT

public:
    explicit DelA(QWidget *parent = nullptr);
    ~DelA();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::DelA *ui;
    PopUp *popUp;
};

#endif // DELA_H
