#ifndef CORW_H
#define CORW_H

#include <QDialog>
#include "popup.h"

namespace Ui {
class CorW;
}

class CorW : public QDialog
{
    Q_OBJECT

public:
    explicit CorW(QWidget *parent = nullptr);

    ~CorW();

private slots:

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::CorW *ui;
    PopUp *popUp;

};

#endif // CORW_H
