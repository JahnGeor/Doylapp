#include "cora.h"
#include "ui_cora.h"
#include <QTextCodec>
#include <QDebug>
#include "writer.h"
#include <QTextStream>

CorA::CorA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CorA)
{
    setWindowIcon(QIcon(":/img/img/detective.png"));
    ui->setupUi(this);
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfcodec);
    popUp = new PopUp();

    QFile file1("data//genre.txt");
    QString data;

    if(!file1.open(QIODevice::ReadOnly))
    return;

    data=file1.readLine();
    QStringList lst1;
    lst1 = data.split(" ");

    qDebug() << lst1.at(3) << lst1.at(4);

    ui->comboBox->clear();
    ui->comboBox->addItems(lst1);

    file1.close();

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
            ui->comboBox_2->addItem(dx);
        }
    } else ui->comboBox_2->addItem("Писателей не найдено");

    file.close();


}

CorA::~CorA()
{
    delete ui;
}

void CorA::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    ui->comboBox_3->clear();
    Art a;
    QStringList lst;
    QString s;
    QFile file("data//"+QString::number(idsearch(arg1))+"//art.txt");
    if(file.open(QIODevice::ReadOnly)) {
        while(!file.atEnd()) {
        s = file.readLine();

        ui->comboBox_3->addItem(s.split(" ")[1].replace("_", " "));
        }
    } else ui->comboBox_3->addItem("Произведений не найдено");


}

void CorA::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    Art a;

    a.finda(idsearch_2(arg1, idsearch(ui->comboBox_2->currentText())), idsearch(ui->comboBox_2->currentText()));
    QDate date(a.date.toInt(),1,1);
    qDebug() << a.date;
    ui->lineEdit->setText(a.name.replace("_", " "));
    ui->comboBox->setCurrentText(a.genre);
    ui->dateEdit->setDate(date);
    ui->plainTextEdit->setPlainText(a.info);

}

void CorA::on_pushButton_clicked()
{

    try {    if(ui->comboBox_3->currentText()=="Произведений не найдено"||ui->comboBox_2->currentText()=="Писателей не найдено") {
            popUp->setPopupText("Произведение не выбрано!");
            popUp->show();
        }
        else {
        QFile file2("data//"+QString::number(idsearch(ui->comboBox_2->currentText()))+"//"+QString::number(idsearch_2(ui->comboBox_3->currentText().replace(" ", "_"), idsearch(ui->comboBox_2->currentText())))+".txt");
        if(file2.open(QIODevice::WriteOnly)) {
            QTextStream b(&file2);
            b << ui->plainTextEdit->toPlainText();
        }

        qDebug() << idsearch_2(ui->comboBox_3->currentText().replace(" ", "_"), idsearch(ui->comboBox_2->currentText()));
        QString s = QString::number(idsearch_2(ui->comboBox_3->currentText().replace(" ", "_"), idsearch(ui->comboBox_2->currentText())))+" "+ui->lineEdit->text().replace(" ", "_")+" "+ui->dateEdit->date().toString("yyyy")+" "+ui->comboBox->currentText()+" "+QString::number(idsearch(ui->comboBox_2->currentText()))+"\n";
        QStringList lst;
        QFile file("data//"+QString::number(idsearch(ui->comboBox_2->currentText())) + "//art.txt");
        if(file.open(QIODevice::ReadOnly)) {
            while(!file.atEnd()) {
            lst << file.readLine();
            }

            for(int i = 0; i < lst.size(); i++) {

                if(lst.at(i).split(" ").at(0).toInt() == idsearch_2(ui->comboBox_3->currentText(), idsearch(ui->comboBox_2->currentText()))) {
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



        CorA::close();
        popUp->setPopupText("Информация о произведении успешно изменена!");
        popUp->show();

        }}

    catch (int e) {
        popUp->setPopupText("Произошла ошибка! Номер ошибки: "+QString::number(e)+".");
        popUp->show();
        CorA::close();
        }

}





void CorA::on_pushButton_2_clicked()
{
    CorA::close();
}
