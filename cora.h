#ifndef CORA_H
#define CORA_H

#include <QDialog>
#include "popup.h"

namespace Ui {
class CorA;
}

class CorA : public QDialog
{
    Q_OBJECT

public:
    explicit CorA(QWidget *parent = nullptr);
    ~CorA();

private slots:
    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_comboBox_3_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CorA *ui;
    PopUp *popUp;
};

#endif // CORA_H
