#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include "serialRead.h"
// #include "checkChar.h"

#include <QSizePolicy>
#include <iostream>
#include <Windows.h>
#include <string>



bool playing =false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);// removes default number column4
    ui->pauseButton->setText("Start Recording");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectButton_clicked()
{
    ui->label->setText(ui->portSelect->text());
    //ui->tableWidget->insertRow(0);
    //ui->tableWidget->setItem(0,0, new QTableWidgetItem(ui->portSelect->text()));
    QString pt = ui->portSelect->text();

    LPCWSTR port = reinterpret_cast<LPCWSTR>(pt.constData()); // convert QString input to lpwstr requirement
    serialSetup(port);

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

