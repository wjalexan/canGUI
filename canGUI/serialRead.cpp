#include <iostream>
#include <Windows.h>
#include <string>
#include "mainwindow.h"
#include "ui_mainwindow.h"


/*
int checkType(char input) {
    int status = -1;
    char set[] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','a','b','c','d','e','f',' ' };
    for (int i = 1; i < sizeof(set); i++) {
        if (input == set[i] && status == -1) {
            status = 0;
        }
        else if (input == '>' && status == -1) {
            std::cout << std::endl;
        }
    }
    return status;
}
*/

int MainWindow::serialRead(LPCWSTR port) {
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
        szBuff[dwBytesRead] = '\0'; // Add null terminator

        //for (int i = 0; i < 255; i++) {
        //    if (checkType(char(szBuff[i])) == 0) {
        //        std::cout << szBuff[i];
        //    }
        //}


        for (int i = 0; i < 255; i++){
            if (checkChar(szBuff[i]) == 's'){
                std::string id;
                std::string rtr;
                std::string ide;
                std::string dlc; // dlc denotes no. of bytes in data section
                std::string data; // data bits
                int dataPos; // position of data bits in array
                int dataLen; // length of data (dlc)
                //ui->label->setText(QString::number(IDlen(szBuff, i)));
                //ui->label->setText(QString::number(i));
                ui->tableWidget->insertRow(0); // new row in table
                //ui->tableWidget->setItem(0,0, new QTableWidgetItem(szBuff.substr(i, IDlen(szBuff,i)))));

                for (int j = 0; j < IDlen(szBuff, i)-1; j++){
                    id += szBuff[j+1]; // set 'id' variable to packet id
                }

                for (int j = 0; j < 2; j++){
                    rtr += szBuff[j+i+IDlen(szBuff, i)+1]; // set 'rtr' variable to packet rtr
                    ide += szBuff[j+i+IDlen(szBuff, i)+4]; // set 'ide' variable to packet ide
                }

                dataPos = i+IDlen(szBuff, i)+7;
                data = szBuff[dataPos];
                for (int j = 0; j < 16; j++){
                    if (checkChar(szBuff[dataPos+j]) == 'e'){
                        dataLen = j;
                    }
                }
                ui->label->setText(QString::number(i));


                ui->tableWidget->setItem(0,0, new QTableWidgetItem(id.c_str())); // print id in table
                ui->tableWidget->setItem(0,1, new QTableWidgetItem(rtr.c_str())); // print rtr in table
                ui->tableWidget->setItem(0,2, new QTableWidgetItem(ide.c_str())); // print ide in table
                ui->tableWidget->setItem(0,3, new QTableWidgetItem(dlc.c_str())); // print ide in table
                ui->tableWidget->setItem(0,4, new QTableWidgetItem(data.c_str())); // print data in table
                break;
            }
        }


        //ui->label->setText(QString(checkChar(szBuff[0])));
        //if (checkChar(szBuff[0]) == 's'){
        //    //ui->label->setText(QString::number(IDlen(szBuff, 0)));
        //    ui->label->setText("du");
        //}


        //ui->label->setText("Connected!");
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0, new QTableWidgetItem(szBuff));

        memset(szBuff, '\0', sizeof(szBuff)); // Clear buffer
        CloseHandle(hSerial); // Close handle

    }
    //}
    return 0;


    CloseHandle(hSerial); // Close handle
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
    return 0;


    CloseHandle(hSerial); // Close handle
}
