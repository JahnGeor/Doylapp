#include "addw.h"
#include "ui_addw.h"
#include <QDebug>
#include <QDir>
#include <QTextCodec>
AddW::AddW(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddW)
{
    setWindowIcon(QIcon(":/img/img/detective.png"));
    ui->setupUi(this);
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfcodec);
    popUp = new PopUp();


}

AddW::~AddW()
{
    delete ui;
}

void AddW::on_pushButton_2_clicked()
{
    AddW::close();
}

void AddW::pullin(Writer &w) {
    w.fName = ui->lineEdit->text();
    w.name = ui->lineEdit_2->text();
    w.sName = ui->lineEdit_3->text();
    w.date = ui->dateEdit->date().toString("dd/MM/yyyy");
    w.bio = ui->plainTextEdit->toPlainText();
    w.country = ui->lineEdit_4->text();

}

bool AddW::wrcheck(Writer &w) {
    QFile file("data//writers.txt");
    Writer dump;
    QStringList lst;
    if(file.open(QIODevice::ReadOnly)) {
        QString dx;
        while(!file.atEnd()) {
            dx = file.readLine();
            qDebug() << dx;
            dx.remove("\r");
            dx.remove("\n");
            qDebug() << dx;
            lst = dx.split(" ");
            qDebug() << "!" << (w.fName == lst.at(1) && w.name == lst.at(2) && w.sName == lst.at(3) && w.date == lst.at(4) && w.country == lst.at(5) );
            if((w.fName == lst.at(1) && w.name == lst.at(2) && w.sName == lst.at(3) && w.date == lst.at(4) && w.country == lst.at(5))) {
                file.close();
                return 0;
            }
        }

        w.id = lst.at(0).toInt()+1;
        file.close();
        return 1;
    } else {
        QFile file("data//writers.txt");
        if(file.open(QIODevice::WriteOnly)) {
            w.id = 1;
            file.close();
            return 1;

        }

    }

}

void AddW::on_pushButton_clicked()
{

    try {
        if(ui->lineEdit->text()==""||ui->lineEdit_2->text()==""||ui->lineEdit_3->text()==""||ui->lineEdit_4->text()==""||ui->plainTextEdit->toPlainText()=="") {

            popUp->setPopupText("Заполните пустые поля!");
            popUp->show();
        }
        else{

        Writer w;
        pullin(w);

        //qDebug() << wrcheck(w);
        if(wrcheck(w)) {
            QFile file("data//writers.txt");
            if(file.open(QIODevice::Append)) {
                QTextStream out(&file);
                out << w.id << " ";
                out << w.fName << " ";
                out << w.name << " ";
                out << w.sName << " ";
                out << w.date << " ";
                out << w.country << endl;
            }

            file.close();

            QDir dire;
            dire.mkdir("data//" + QString::number(w.id));

            QFile biofile("data//" + QString::number(w.id)+"//bio.txt");
            if(biofile.open(QIODevice::WriteOnly)) {
                QTextStream out(&biofile);
                out << ui->plainTextEdit->toPlainText();
            }

            biofile.close();
            AddW::close();
            popUp->setPopupText("Писатель успешно добавлен!");
            popUp->show();
        } else {

            popUp->setPopupText("Писатель не может быть добавлен, так как уже находится в базе!");
            popUp->show();
        }}
    }


    catch (int e) {
        popUp->setPopupText("Произошла ошибка! Номер ошибки: "+QString::number(e)+".");
        popUp->show();
        AddW::close();
        }

}
