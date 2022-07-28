#ifndef DELW_H
#define DELW_H

#include <QDialog>
#include "popup.h"

namespace Ui {
class DelW;
}

class DelW : public QDialog
{
    Q_OBJECT

public:
    explicit DelW(QWidget *parent = nullptr);
    ~DelW();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DelW *ui;
    PopUp *popUp;
};

#endif // DELW_H
