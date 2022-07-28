#ifndef ADDA_H
#define ADDA_H

#include <QDialog>
#include "writer.h"
#include "popup.h"
namespace Ui {
class AddA;
}

class AddA : public QDialog
{
    Q_OBJECT

public:
    explicit AddA(QWidget *parent = nullptr);
    ~AddA();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddA *ui;
    PopUp *popUp;
};

#endif // ADDA_H
