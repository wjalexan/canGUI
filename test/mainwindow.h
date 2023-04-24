#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>

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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    int serialRead(LPCWSTR port);

    //char checkChar(char inpt);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
