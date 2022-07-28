#ifndef FIND_H
#define FIND_H

#include <QDialog>
#include "popup.h"

namespace Ui {
class Find;
}

class Find : public QDialog
{
    Q_OBJECT

public:
    explicit Find(QWidget *parent = nullptr);
    ~Find();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Find *ui;
    PopUp *popUp;
};

#endif // FIND_H
