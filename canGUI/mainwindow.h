#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QThread>
#include "workerThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool playing = false;

private slots:
    void on_connectButton_clicked();

    void on_pauseButton_clicked();


private:
    Ui::MainWindow *ui;

    int serialRead(LPCWSTR port);

    int serialSetup(LPCWSTR port);

    char checkChar(char inpt);

    int findEnd(char data[255]);

    int IDlen(std::string can, int start);

    workerThread * readLoop;

    //workerThread *thread_;

};




#endif // MAINWINDOW_H
