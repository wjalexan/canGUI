#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QThread>
//#include "workerThread.h"


bool playing = false;




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

    void canInterpret(char buffer[256]);


private:
    Ui::MainWindow *ui;

    int serialRead(LPCWSTR port);

    int serialSetup(LPCWSTR port);

    //char checkChar(char inpt);

    //int findEnd(char data[256]);

    //int IDlen(std::string can, int start);

    //workerThread* readLoop;

};




// class for worker thread

class loopThread : public QThread { // definition of loopThread used to run the infinite loop, getting the data to dismplay on screen
    Q_OBJECT

signals:
    void canBufferAvailable(char canBuffer[256]);


public:
    void stop(){
        playing = false;
    }

    loopThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run(LPCWSTR port);

private:

};





// other function definitions:

char checkChar(char inpt){
    switch (inpt){
    case '^':
        return 'b'; // searches for starting character
        break;

    case '*':
        return 'f'; // searces for termination character
        break;

    case ',':
        return 's'; // searches for separation character
        break;

    default:
        if ((int(inpt) >= 64 && int(inpt) <= 90) || (int(inpt) >= 48 && int(inpt) <= 57)) {
            return 'v'; // searches for valid data bit
        }
        else {
            return 'n';
        }
    }
}

int IDlen(std::string can, int start){
    for (int i = 1; i < 255-start; i++){
        if (checkChar(can[start + i]) == 's'){
            return i;
            break;
        }
    }
    return -1;
}


int findEnd(char data[255]){
    for (int j = 255; j > 0; j--){
        if (checkChar(data[j]) == 'f'){
            return j;
            break;
        }
    }
}




#endif // MAINWINDOW_H
