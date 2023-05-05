#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "workerThread.h"

#include <QSizePolicy>
#include <QThread>
#include <iostream>
#include <Windows.h>
#include <string>
#include <unistd.h>


//bool playing =false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);// removes default number column4
    ui->pauseButton->setText("Start Recording");
    ui->label->setText("Not Connected");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_connectButton_clicked()
{
    ui->label->setText("Connecting...");

    QString pt = ui->portSelect->text();
    LPCWSTR port = reinterpret_cast<LPCWSTR>(pt.constData()); // convert QString input to lpwstr requirement
    serialSetup(port);
    /*QThread *thread = QThread::create([&]{
        while(playing == true)
            ui->connectButton->setText("d");
            usleep(1000000);
            ui->connectButton->setText(" ");
            usleep(1000000);
    });
    thread->start();*/
}





void MainWindow::on_pauseButton_clicked()
{
    if (ui->pauseButton->text() == "Pause"){
        ui->pauseButton->setText("Start Recording");
        playing = false;
        ui->label->setText("");

    }
    else if (ui->pauseButton->text() == "Start Recording"){
        ui->pauseButton->setText("Pause");
        playing = true;
        QString pt = ui->portSelect->text();

        LPCWSTR port = reinterpret_cast<LPCWSTR>(pt.constData()); // convert QString input to lpwstr requirement
        serialRead(port);
    }
}



void loopThread::run(){ // defining run() function when loopThread is called
    while(!running){

    }
}

