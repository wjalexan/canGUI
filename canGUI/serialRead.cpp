#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <QThread>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workerThread.h"




int MainWindow::serialRead(LPCWSTR port) {
    playing = false;
    //QThread *thread = QThread::create([&]{
    //    while(playing == false)
    //        ui->connectButton->setText("test");
    // Define variables
    // HANDLE hSerial; // Handle for serial port
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
        // printf("Error opening serial port\n");
        ui->label->setText("Error opening serial port");
        return 1;
    }

    // Set serial port parameters
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        // printf("Error getting serial port state\n");
        ui->label->setText("Error getting serial port state");
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600; // Baud rate
    dcbSerialParams.ByteSize = 8; // Data size
    dcbSerialParams.StopBits = ONESTOPBIT; // Stop bit
    dcbSerialParams.Parity = NOPARITY; // Parity

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        // printf("Error setting serial port state\n");
        ui->label->setText("Error getting serial port state");
        return 1;
    }
    //ui->label->setText("Connected!");


    // Read data from serial port
    if (!ReadFile(hSerial, szBuff, sizeof(szBuff) - 1, &dwBytesRead, NULL))
    {
        // printf("Error reading from serial port\n");
        ui->label->setText("Error reading from serial port");
        //break;
    }


    if (dwBytesRead > 0)
    {
        szBuff[dwBytesRead] = '\0'; // Add null terminator

        //for (int i = 0; i < 255; i++) {q
        //    if (checkType(char(szBuff[i])) == 0) {
        //        std::cout << szBuff[i];
        //    }
        //}

        int position; // variable storing the current position when decoding CAN messages
        int end = findEnd(szBuff); // variable indicating the last complete packet
        ui->label->clear();

        for(int x = 0; x < end-1; x++){
            for (int i = 0 + x; i < 255; i++){
                if (checkChar(szBuff[i]) == 'b'){
                    std::string id; // packet id
                    std::string rtr; // remote transmission request: denotes whether data is requested
                    std::string ide; // denotes whether an extension is being transmitted
                    std::string dlc; // dlc denotes no. of bytes in data section
                    std::string data[8]; // data bits
                    int dataPos; // position of data bits in array
                    int dataLen; // length of data (dlc)


                    ui->tableWidget->insertRow(0); // new row in table

                    if (IDlen(szBuff, i) != -1){

                        for (int j = 1; j < IDlen(szBuff, i); j++){
                            id += szBuff[j+i]; // set 'id' variable to packet id
                        }

                        for (int j = 0; j < 2; j++){
                            rtr += szBuff[j+i+IDlen(szBuff, i)+1]; // set 'rtr' variable to packet rtr
                            ide += szBuff[j+i+IDlen(szBuff, i)+4]; // set 'ide' variable to packet ide
                        }

                        dataPos = i+IDlen(szBuff, i)+7;
                        //ui->label->setText(QString::number(i+IDlen(szBuff,i)));
                        //data = szBuff[dataPos];
                        for (int j = 0; j < 16; j++){
                            if (checkChar(szBuff[dataPos+j]) == 'f'){
                                dataLen = j;
                                break;
                            }
                        }


                        for (int j = 0; j < dataLen/2; j++){
                            for (int k = 0; k < 2; k++){
                                data[j] += szBuff[2*j+dataPos+k]; // set 'id' variable to packet id
                            }
                        }

                        // convert length integer value to hexadecimal before adding to table
                        std::stringstream len;
                        len << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << dataLen/2;
                        dlc = len.str();


                        ui->tableWidget->setItem(0,0, new QTableWidgetItem(id.c_str())); // print id in table
                        ui->tableWidget->setItem(0,1, new QTableWidgetItem(rtr.c_str())); // print rtr in table
                        ui->tableWidget->setItem(0,2, new QTableWidgetItem(ide.c_str())); // print ide in table
                        ui->tableWidget->setItem(0,3, new QTableWidgetItem(dlc.c_str())); // print dlc in table
                        for (int j = 0; j < dataLen/2; j++){
                            ui->tableWidget->setItem(0,4+j, new QTableWidgetItem(data[j].c_str())); // print data in table
                        }

                        position = dataLen + dataPos;
                        break;
                    }
                }
            }
        x = position;
        }


        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0, new QTableWidgetItem(szBuff));

        memset(szBuff, '\0', sizeof(szBuff)); // Clear buffer

    }

    CloseHandle(hSerial); // Close handle

    return 0;


    //thread->quit();
    //});
    //thread->start();
}









int MainWindow::serialSetup(LPCWSTR port){
    // Define variables
    // HANDLE hSerial; // Handle for serial port
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
        // printf("Error opening serial port\n");
        ui->label->setText("Error opening serial port");
        return 1;
    }

    // Set serial port parameters
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        // printf("Error getting serial port state\n");
        ui->label->setText("Error getting serial port state");
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600; // Baud rate
    dcbSerialParams.ByteSize = 8; // Data size
    dcbSerialParams.StopBits = ONESTOPBIT; // Stop bit
    dcbSerialParams.Parity = NOPARITY; // Parity

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        // printf("Error setting serial port state\n");
        ui->label->setText("Error getting serial port state");
        return 1;
    }
    ui->label->setText("Connected!");
    /*while (1)
    {*/
    // Read data from serial port
    if (!ReadFile(hSerial, szBuff, sizeof(szBuff) - 1, &dwBytesRead, NULL))
    {
        // printf("Error reading from serial port\n");
        ui->label->setText("Error reading from serial port");
        //break;
    }


    if (dwBytesRead > 0)
    {
        ui->label->setText("Connected!");
        memset(szBuff, '\0', sizeof(szBuff)); // Clear buffer
        CloseHandle(hSerial); // Close handle
    }

    CloseHandle(hSerial); // Close handle
    return 0;
}



void workerThread::run(){
    /*while(playing == true){
        using namespace Ui;
        MainWindow->ui->connectButton->setText("d");
        usleep(1000000);
        ui->connectButton->setText(" ");
        usleep(1000000);
    }*/
}
