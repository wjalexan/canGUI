#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <iostream>
#include <fstream>

int main()
{
    // Create a handle for the serial port
    HANDLE hSerial;

    // Open the serial port
    hSerial = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    // Check if the serial port is open
    if(hSerial == INVALID_HANDLE_VALUE){
        std::cout << "Error opening serial port" << std::endl;
    }

    // Set the parameters of the serial port
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cout << "Error getting state of serial port" << std::endl;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cout << "Error setting state of serial port" << std::endl;
    }

    // Write data to serial port
    char data[] = "Hello";
    
    DWORD dwBytesWritten;
    
    if (!WriteFile(hSerial, data, sizeof(data), &dwBytesWritten, NULL)) {
        std::cout << "Error writing data to serial port" << std::endl;
    }

     // Read data from serial port
     char buffer[5];
     
     DWORD dwBytesRead;
     
     if(!ReadFile(hSerial, buffer, sizeof(buffer), &dwBytesRead, NULL))
         std::cout << "Error reading data from serial port" << std::endl;

     // Print the result
     std::cout << "Result: " << buffer << std::endl;

     // Close the serial port
     CloseHandle(hSerial);

     return 0;
}