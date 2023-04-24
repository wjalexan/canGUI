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

    int serialRead(LPCWSTR port);

    int serialSetup(LPCWSTR port);

    char checkChar(char inpt);

    int IDlen(std::string can, int start);

    void on_pauseButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
