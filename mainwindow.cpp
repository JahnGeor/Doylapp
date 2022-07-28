#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addw.h"
#include "adda.h"
#include "corw.h"
#include "cora.h"
#include "dela.h"
#include "delw.h"
#include "find.h"
#include <QPixmap>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/img/img/detective.png"));
    ui->setupUi(this);
    QPixmap pix(":/img/img/detective.png");

    ui->Image1->setPixmap(pix.scaled(300,300,Qt::KeepAspectRatio));
    popUp = new PopUp();
    popUp->setPopupText("Приветствую в приложении DoylApp! Это информативное окно сообщает об успешности действий!");
    popUp->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}








void MainWindow::on_action_7_triggered()
{
    qApp->quit();
}



void MainWindow::on_action_2_triggered()
{
    AddW win;
    win.setModal(true);
    win.exec();

}

void MainWindow::on_action_3_triggered()
{
    AddA win;
    win.setModal(true);
    win.exec();
}

void MainWindow::on_action_9_triggered()
{
    CorW win;
    win.setModal(true);
    win.exec();
}

void MainWindow::on_action_10_triggered()
{
    CorA win;
    win.setModal(true);
    win.exec();
}

void MainWindow::on_action_11_triggered()
{
    DelA win;
    win.setModal(true);
    win.exec();
}

void MainWindow::on_action_12_triggered()
{
    DelW win;
    win.setModal(true);
    win.exec();
}

void MainWindow::on_action_5_triggered()
{
    Find win;
    win.setModal(true);
    win.exec();
}

void MainWindow::on_action_8_triggered()
{
    QMessageBox mb("Doyleapp",
                               "Программа написана в качестве курсовой работы за первый курс.\nРаботу выполнил: студент Ишуткин Е.И., ИВБО-01-18 (пр-щая. ИВБО-12-18)",
                               QMessageBox::NoIcon,
                               QMessageBox::Ok | QMessageBox::Default,
                               QMessageBox::NoButton,
                               QMessageBox::NoButton);

    mb.setWindowIcon(QIcon(":/img/img/detective.png"));

    mb.exec();
}
