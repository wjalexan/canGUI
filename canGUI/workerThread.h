
#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QObject>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"


class workerThread : public QThread {
    Q_OBJECT

public:
    workerThread(MainWindow* mainWindow, QObject* parent = nullptr) :
        QThread(parent), m_mainWindow(mainWindow) {}
    void run() override;
private:
    QMainWindow *m_mainWindow;
};


#endif // WORKERTHREAD_H
