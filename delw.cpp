#include "delw.h"
#include "ui_delw.h"
#include "QTextCodec"
#include <QDebug>
#include "writer.h"
#include <QTextStream>


DelW::DelW(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelW)
{
    setWindowIcon(QIcon(":/img/img/detective.png"));
    ui->setupUi(this);
    popUp = new PopUp();
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfcodec);

    QStringList lst;
    QFile file("data//writers.txt");

    QString dx;

    if(file.open(QIODevice::ReadOnly)) {


        while(!file.atEnd()) {
            dx = file.readLine();
            dx.remove("\r\n");
            lst = dx.split(" ");
            //qDebug() << lst.at(1);
            //qDebug() << " " + lst.at(2) + " " + lst.at(3);
            dx = lst.at(1) + " " + lst.at(2) + " " + lst.at(3);
            //qDebug() << dx;
            ui->comboBox->addItem(dx);
        }
    } else ui->comboBox->addItem("Писателей не найдено");

    file.close();

}

DelW::~DelW()
{
    delete ui;
}

void DelW::on_pushButton_clicked()
{
    try {
        if(ui->comboBox->currentText()=="Писателей не найдено") {

            popUp->setPopupText("Писатель не был выбран!");
            popUp->show();
        } else {

        QDir dire("data//"+QString::number(idsearch(ui->comboBox->currentText())));
        removeFolder(dire);
        QFile file("data//writers.txt");
        QStringList lst;
        if(file.open(QIODevice::ReadOnly)) {
            while(!file.atEnd()) lst << file.readLine();
            file.close();
            }

        for(int i = 0; i < lst.size(); i++) {
        if(lst[i].split(" ").at(0).toInt()==idsearch(ui->comboBox->currentText())) lst[i] = "";
        }
        qDebug() << lst;

        if(file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            foreach (QString s, lst) {
                out << s;
            }
            file.close();
        }

        if(lst.size() <= 1) file.remove();

        DelW::close();
        popUp->setPopupText("Писатель успешно удален!");
        popUp->show();
        }
    }

    catch (int e) {
        popUp->setPopupText("Произошла ошибка! Номер ошибки: "+QString::number(e)+".");
        popUp->show();
        DelW::close();
        }

}

void DelW::on_pushButton_2_clicked()
{
    DelW::close();
}
