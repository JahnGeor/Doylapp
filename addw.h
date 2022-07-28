#ifndef ADDW_H
#define ADDW_H
#include "popup.h"
#include <QDialog>
#include "writer.h"
namespace Ui {
class AddW;
}

class AddW : public QDialog
{
    Q_OBJECT

public:
    bool wrcheck(Writer &a);
    void pullin(Writer &a);
    explicit AddW(QWidget *parent = nullptr);
    ~AddW();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddW *ui;
    PopUp *popUp;
};

#endif // ADDW_H
