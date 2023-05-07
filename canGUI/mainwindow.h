#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QThread>

//#include "checkAlgorithms.h"
//#include "workerThread.h"







// class for GUI window


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
    void on_connectButton_clicked();

    void on_pauseButton_clicked();

public slots:

    void canInterpret(std::string strBuffer);

private:
    Ui::MainWindow *ui;

    int serialRead(LPCWSTR port);

    int serialSetup(LPCWSTR port);

    char checkChar(char inpt);

    int findEnd(char data[256]);

    int IDlen(std::string can, int start);

};




// class for worker thread

class loopThread : public QThread { // definition of loopThread used to run the infinite loop, getting the data to dismplay on screen
    Q_OBJECT

signals:
    void canBufferAvailable(std::string buffer);


public:
    void stop(){
        quit();
    }

    loopThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() override;

private:

};


#endif // MAINWINDOW_H
