#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "workerThread.h"
//#include "checkAlgorithms.h"

#include <QSizePolicy>
#include <QThread>
#include <iostream>
#include <Windows.h>
#include <string>
#include <unistd.h>
#include <sstream>
#include <iomanip>


bool playing = false;
LPCWSTR port;


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

        port = reinterpret_cast<LPCWSTR>(pt.constData()); // convert QString input to lpwstr requirement
//        serialRead(port);
        loopThread *thread = new loopThread(this);
//        connect(thread, &loopThread::canBufferAvailable, this, &MainWindow::canInterpret);
        connect(thread, SIGNAL(canBufferAvailable(std::string)), this, SLOT(canInterpret(std::string)));
        thread->start();
    }
}







void loopThread::run(){ // defining run() function when loopThread is called

    playing = true;
    DCB dcbSerialParams = { 0 }; // Structure for serial port parameters
    DWORD dwBytesRead = 0; // Number of bytes read from serial port
    char szBuff[256] = { 0 }; // Buffer for data from serial port

    // Open serial port
    HANDLE hSerial = CreateFile((port), GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        //ui->label->setText("Error opening serial port");
        //return 1;
        stop();
    }

    // Set serial port parameters
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        //ui->label->setText("Error getting serial port state");
        //return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600; // Baud rate
    dcbSerialParams.ByteSize = 8; // Data size
    dcbSerialParams.StopBits = ONESTOPBIT; // Stop bit
    dcbSerialParams.Parity = NOPARITY; // Parity

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        //ui->label->setText("Error getting serial port state");
        //return 1;
    }
    while(1){
        if (playing == false) {
            break;
        }
        // Read data from serial port
        if (!ReadFile(hSerial, szBuff, sizeof(szBuff) - 1, &dwBytesRead, NULL))
        {
            //ui->label->setText("Error reading from serial port");
            break;
        }


        if (dwBytesRead > 0)
        {

            std::string stringBuff; // convert szBuff variable to std::string so it can be passed through slot
            szBuff[dwBytesRead] = '\0'; // Add null terminator
            for (int i = 0; i < 256; i++) {
                stringBuff += szBuff[i];
            }

//            stringBuff = "jfkasdhflaskdjfksldajflksdjaflksdajflksdajfl";

            emit canBufferAvailable(stringBuff); // signal calling function to interpret serial messages


            memset(szBuff, '\0', sizeof(szBuff)); // Clear buffer

        }
//        break;

    }
    CloseHandle(hSerial); // Close handle
}




void MainWindow::canInterpret(std::string strBuffer) { // function for decoding CAN message buffer

    char buffer[256] = { 0 }; // initialize buffer variable as a character
    for (int i = 0; i < 256; i++){
        buffer[i] = strBuffer[i]; // populate buffer variable with contents of string
    }

    int position = 0; // variable storing the current position when decoding CAN messages
    int end = findEnd(buffer); // variable indicating the last complete packet



    for (int x = 0; x < end - 1; x++) {
        for (int i = 0 + x; i < 256; i++) {
            if (checkChar(buffer[i]) == 'b') {
                std::string id = ""; // packet id
                std::string rtr = ""; // remote transmission request: denotes whether data is requested
                std::string ide = ""; // denotes whether an extension is being transmitted
                std::string dlc = ""; // dlc denotes no. of bytes in data section
                std::string data[8]; // data bits
                int dataPos = 0; // position of data bits in array
                int dataLen = 0; // length of data (dlc)


                ui->tableWidget->insertRow(0); // new row in table

                if (IDlen(buffer, i) != -1) {

                    for (int j = 1; j < IDlen(buffer, i); j++) {
                        id += buffer[j + i]; // set 'id' variable to packet id
                    }

                    for (int j = 0; j < 2; j++) {
                        rtr += buffer[j + i + IDlen(buffer, i) + 1]; // set 'rtr' variable to packet rtr
                        ide += buffer[j + i + IDlen(buffer, i) + 4]; // set 'ide' variable to packet ide
                    }

                    dataPos = i + IDlen(buffer, i) + 7;
                    for (int j = 0; j < 16; j++) {
                        if (checkChar(buffer[dataPos + j]) == 'f') { // finding position of data - for loop iterates until it finds the end character
                            dataLen = j;
                            break;
                        }
                    }


                    for (int j = 0; j < dataLen / 2; j++) {
                        for (int k = 0; k < 2; k++) { // finding position of packet ID using iterative for loop
                            data[j] += buffer[2 * j + dataPos + k]; // set 'id' variable to packet id
                        }
                    }

                    // convert length integer value to hexadecimal before adding to table
                    std::stringstream len;
                    len << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << dataLen / 2;
                    dlc = len.str();


                    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(id.c_str())); // print id in table
                    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(rtr.c_str())); // print rtr in table
                    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(ide.c_str())); // print ide in table
                    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(dlc.c_str())); // print dlc in table
                    for (int j = 0; j < dataLen / 2; j++) {
                        ui->tableWidget->setItem(0, 4 + j, new QTableWidgetItem(data[j].c_str())); // print data in table
                    }

                    position = dataLen + dataPos;
                    break;
                }
            }
        }
        x = position;
    }
//    playing = false;
}
