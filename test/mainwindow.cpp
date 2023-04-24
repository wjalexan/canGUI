#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSizePolicy>
#include "serialRead.h"
//#include "serialWrite.h"
#include <iostream>
#include <Windows.h>
#include <string>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);// removes default number column
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

    //LPCWSTR port = reinterpret_cast<LPCWSTR>(pt.constData()); // convert QString input to lpwstr requirement
    //serialRead(port);

}


void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Hello"));
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget->insertRow(0);
}



