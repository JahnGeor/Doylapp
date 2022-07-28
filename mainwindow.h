#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "popup.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:







    void on_action_7_triggered();



    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

    void on_action_11_triggered();

    void on_action_12_triggered();

    void on_action_5_triggered();

    void on_action_8_triggered();

private:
    Ui::MainWindow *ui;
    PopUp *popUp;
};
#endif // MAINWINDOW_H
