#include "adda.h"
#include "ui_adda.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QTextCodec>
AddA::AddA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddA)
{
    setWindowIcon(QIcon(":/img/img/detective.png"));
    ui->setupUi(this);
    popUp = new PopUp();
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfcodec);

    QFile file("data//genre.txt");
    QString data;

    if(!file.open(QIODevice::ReadOnly))
    return;

    data=file.readLine();
    QStringList lst;
    lst = data.split(" ");

    qDebug() << lst.at(3) << lst.at(4);

    ui->comboBox->clear();
    ui->comboBox->addItems(lst);

    file.close();

    QStringList lst2;
    QFile file_2("data//writers.txt");

    QString dx;
    QStringList lst3;

    if(file_2.open(QIODevice::ReadOnly)) {


        while(!file_2.atEnd()) {
            dx = file_2.readLine();
            dx.remove("\r\n");
            lst2 = dx.split(" ");
            qDebug() << lst2.at(1);
            qDebug() << " " + lst2.at(2) + " " + lst2.at(3);
            dx = lst2.at(1) + " " + lst2.at(2) + " " + lst2.at(3);
            qDebug() << dx;
            ui->comboBox_2->addItem(dx);
        }
    } else ui->comboBox_2->addItem("Писатель не выбран");



}

AddA::~AddA()
{
    delete ui;
}




void AddA::on_pushButton_clicked()
{
    try {

        if(ui->plainTextEdit->toPlainText()==""||ui->lineEdit->text()=="") {
            popUp->setPopupText("Заполните пустые поля!");
            popUp->show();
        }

        else if(ui->comboBox_2->currentText() == "Писатель не выбран") {



            popUp->setPopupText("Не выбран писатель! Добавьте писателя в главном меню.");
            popUp->show();

        }

        else {
        Art ar;

        ar.idw = idsearch(ui->comboBox_2->currentText());
        ar.name = ui->lineEdit->text().replace(" ", "_");
        ar.info = ui->plainTextEdit->toPlainText();
        ar.date = ui->dateEdit->date().toString("yyyy");
        ar.genre = ui->comboBox->currentText();

        QFile file("data//"+QString::number(idsearch(ui->comboBox_2->currentText()))+"//art.txt");

        if(!file.open(QIODevice::ReadOnly)) {
            file.close();
            QFile file_2("data//"+QString::number(idsearch(ui->comboBox_2->currentText()))+"//art.txt");
            if(file_2.open(QIODevice::WriteOnly)) {
                ar.id = 1;
                file_2.close();
            }

        }   else {
                QString a;
                QStringList lst;
                while(!file.atEnd()) {
                    a = file.readLine();
                    a.remove("\r\n");
                    lst = a.split(" ");
                }
            file.close();
            ar.id = lst.at(0).toInt()+1;

        }

        QFile file_3("data//"+QString::number(idsearch(ui->comboBox_2->currentText()))+"//art.txt");

        if(file_3.open(QIODevice::Append)) {
            QTextStream out(&file_3);
            out << ar.id << " " << ar.name << " " << ar.date << " " << ar.genre << " " << ar.idw << endl;
        }
        file_3.close();
        qDebug() << ar.id;

        QFile artf("data//"+QString::number(idsearch(ui->comboBox_2->currentText()))+"//"+QString::number(ar.id)+".txt");
        if(artf.open(QIODevice::WriteOnly)) {
            QTextStream out(&artf);
            out << ar.info;
        }
        artf.close();

        AddA::close();
        popUp->setPopupText("Произведение добавлено в базу!");
        popUp->show();
        }
    }


    catch (int e) {
        popUp->setPopupText("Произошла ошибка! Номер ошибки: "+QString::number(e)+".");
        popUp->show();
        AddA::close();
        }
}

void AddA::on_pushButton_2_clicked()
{
    AddA::close();
}
