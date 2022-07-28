#include "corw.h"
#include "ui_corw.h"
#include <QTextCodec>
#include <QDebug>
#include "writer.h"
#include <QTextStream>
CorW::CorW(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CorW)
{
    setWindowIcon(QIcon(":/img/img/detective.png"));
    ui->setupUi(this);
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfcodec);
    popUp = new PopUp();
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
        file.close();
    } else ui->comboBox->addItem("Писатель не выбран");

}

CorW::~CorW()
{
    delete ui;
}






void CorW::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(ui->comboBox->currentText()!="Писатель не выбран") {


    Writer w;
    QStringList lst;


    //qDebug() << arg1;
    //qDebug() << idsearch(arg1);
    w.findw(idsearch(arg1));
    lst = w.date.split("/");


    QDate date(lst.at(2).toInt(), lst.at(1).toInt(), lst.at(0).toInt());
    ui->lineEdit->setText(w.fName);
    ui->lineEdit_2->setText(w.name);
    ui->lineEdit_3->setText(w.sName);
    ui->dateEdit->setDate(date);
    ui->lineEdit_4->setText(w.country);

    ui->plainTextEdit->setPlainText(w.bio);
    }
}

void CorW::on_pushButton_2_clicked()
{
    CorW::close();
}

void CorW::on_pushButton_clicked()
{
    try {
        if(ui->comboBox->currentText() == "Писатель не выбран") {

            popUp->setPopupText("Изменения невозможны, не выбран писатель!");
            popUp->show();
        }

        else {



        QFile file("data//writers.txt");
        QStringList lst;
        QString s;
        s = QString::number(idsearch(ui->comboBox->currentText()))+" "+ui->lineEdit->text()+" "+ui->lineEdit_2->text()+" "+ui->lineEdit_3->text()+" "+ui->dateEdit->date().toString("dd/MM/yyyy")+" "+ui->lineEdit_4->text()+"\n";
        qDebug() << s;

        if(file.open(QIODevice::ReadOnly)) {
            while(!file.atEnd()) {
            lst << file.readLine();
            //qDebug() << lst;
            }

            for(int i = 0; i < lst.size(); i++) {

                if(lst.at(i).split(" ").at(0).toInt() == idsearch(ui->comboBox->currentText())) {
                    lst[i]=s;
                }

            }
        }

            file.close();

        if(file.open(QIODevice::WriteOnly)) {
            QTextStream st(&file);
            foreach(QString s, lst) {
                st << s;

            }
        }

        file.close();

        QFile file2("data//"+QString::number(idsearch(ui->comboBox->currentText()))+"//bio.txt");
        if(file2.open(QIODevice::WriteOnly)) {
            QTextStream b(&file2);
            b << ui->plainTextEdit->toPlainText();
        }

        CorW::close();
        popUp->setPopupText("Информация о писателе успешно изменена!");
        popUp->show();
        }
    }

    catch (int e) {
        popUp->setPopupText("Произошла ошибка! Номер ошибки: "+QString::number(e)+".");
        popUp->show();
        CorW::close();
        }

}


