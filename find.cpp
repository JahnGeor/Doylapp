#include "find.h"
#include "ui_find.h"
#include "QTextCodec"
#include <QFile>
#include "writer.h"
Find::Find(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Find)
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

Find::~Find()
{
    delete ui;
}

void Find::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->comboBox_2->clear();

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

void Find::on_pushButton_clicked()
{
    try {
        if(ui->comboBox->currentText()=="Писателей не найдено" || ui->comboBox_2->currentText()=="Произведений не найдено") {
            popUp->setPopupText("Произведение не выбрано!");
            popUp->show();
        }
        else {
        Art a; Writer w;
        QFile file("data//"+QString::number(idsearch(ui->comboBox->currentText()))+"//"+QString::number(idsearch_2(ui->comboBox_2->currentText(), idsearch(ui->comboBox->currentText())))+".txt");
        a.finda(idsearch_2(ui->comboBox_2->currentText(), idsearch(ui->comboBox->currentText())), idsearch(ui->comboBox->currentText()));
        w.findw(idsearch(ui->comboBox->currentText()));
        QString inf = a.name.replace("_", " ") + "\n" + "Год создания: " + a.date + "\nЖанр: " + a.genre + "\n\nОб авторе:\nАвтор: "+w.fName+" "+w.name+" "+w.sName+"\nДата рождения: "+w.date+"\nСтрана: "+w.country+"\nБиография: "+w.bio+"\n---------------------------------------------------------------------\n";

        if(file.open(QIODevice::ReadOnly)) {
            inf = inf + file.readAll();
            ui->plainTextEdit->setPlainText(inf);
            file.close();
        }}
    } catch (int e) {
        popUp->setPopupText("Произошла ошибка! Номер ошибки: "+QString::number(e)+".");
        popUp->show();
        Find::close();
        }
}

void Find::on_pushButton_2_clicked()
{
    Find::close();
}
