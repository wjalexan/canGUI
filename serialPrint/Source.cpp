#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <iostream>
#include <fstream>

int main()
{
    // Define variables
    HANDLE hSerial; // Handle for serial port
    DCB dcbSerialParams = { 0 }; // Structure for serial port parameters
    DWORD dwBytesRead = 0; // Number of bytes read from serial port
    char szBuff[256] = { 0 }; // Buffer for data from serial port

    // Open serial port
    hSerial = CreateFile(_T("COM3"), GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        printf("Error opening serial port\n");
        return 1;
    }

    // Set serial port parameters
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        printf("Error getting serial port state\n");
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600; // Baud rate
    dcbSerialParams.ByteSize = 8; // Data size
    dcbSerialParams.StopBits = ONESTOPBIT; // Stop bit
    dcbSerialParams.Parity = NOPARITY; // Parity

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        printf("Error setting serial port state\n");
        return 1;
    }

    std::ofstream log("log.txt");

    while (1)
    {
        // Read data from serial port
        if (!ReadFile(hSerial, szBuff, sizeof(szBuff) - 1, &dwBytesRead, NULL))
        {
            printf("Error reading from serial port\n");
            break;
        }

        if (dwBytesRead > 0)
        {
            szBuff[dwBytesRead] = '\0'; // Add null terminator

            std::cout << szBuff; // Print data
            log << szBuff; // write to file
            log.flush();

            memset(szBuff, '\0', sizeof(szBuff)); // Clear buffer

        }
    }


    CloseHandle(hSerial); // Close handle
    log.close();

    return 0;
}