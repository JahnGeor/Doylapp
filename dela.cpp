#include "dela.h"
#include "ui_dela.h"
#include <QFile>
#include <QTextStream>
#include "writer.h"
#include <QDebug>
#include <QTextCodec>
DelA::DelA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelA)
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

DelA::~DelA()
{
    delete ui;
}

void DelA::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    Art a;
    QStringList lst;
    QString s;
    QFile file("data//"+QString::number(idsearch(arg1))+"//art.txt");
    if(file.open(QIODevice::ReadOnly)) {
        while(!file.atEnd()) {
        s = file.readLine();

        ui->comboBox_2->addItem(s.split(" ")[1].replace("_", " "));
        }
    } else ui->comboBox_2->addItem("Произведений не найдено");
}

void DelA::on_pushButton_2_clicked()
{

    try {
        if(ui->comboBox_2->currentText() == "Произведений не найдено" || ui->comboBox_2->currentText() == "" ) {

            popUp->setPopupText("Произведение не было выбрано!");
            popUp->show();

        } else {
        QString path = "data//"+QString::number(idsearch(ui->comboBox->currentText())) + "//" + "art.txt";
        QFile file(path);

        QStringList lst;
        if(file.open(QIODevice::ReadOnly)) {

        while(!file.atEnd()) lst << file.readLine();
        file.close();
        for(int i = 0; i < lst.size(); i++) {
            if(lst[i].split(" ").at(0).toInt()==idsearch_2(ui->comboBox_2->currentText(), idsearch(ui->comboBox->currentText()))) {
               lst[i] = "";
            }
        }

        } else qDebug() << "War";

        qDebug() << lst;
        if(file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            foreach (QString s, lst) {
                out<<s;
            }


        }
        file.close();

        if(lst.size() <= 1) file.remove();
        DelA::close();
        popUp->setPopupText("Произведение успешно удалено!");
        popUp->show();
        }
        }
    catch (int e) {
        popUp->setPopupText("Произошла ошибка! Номер ошибки: "+QString::number(e)+".");
        popUp->show();
        DelA::close();
        }
    }







void DelA::on_pushButton_clicked()
{
    DelA::close();
}
