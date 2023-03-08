#include <iostream>
#include <windows.h>
#include <string>

#ifndef SERIALWRITE_H
#define SERIALWRITE_H

int serialWrite(LPCWSTR port, std::string message) { // serialWrite command; eg serialWrite(L"COM3", "hello world")
    HANDLE arduino = CreateFile(
        port,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (arduino == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to open port" << std::endl;
        return -1;
    }

    DCB dcb = { 0 };
    dcb.DCBlength = sizeof(dcb);

    if (!GetCommState(arduino, &dcb))
    {
        std::cerr << "Failed to get comm state" << std::endl;
        CloseHandle(arduino);
        return -1;
    }

    dcb.BaudRate = CBR_9600;
    dcb.ByteSize = 8;

    if (!SetCommState(arduino, &dcb))
    {
        std::cerr << "Failed to set comm state" << std::endl;
        CloseHandle(arduino);
        return -1;
    }

    DWORD bytes_written = 0;

    if (!WriteFile(arduino, message.c_str(), message.size(), &bytes_written, NULL))
    {
        std::cerr << "Failed to write to port" << std::endl;
        CloseHandle(arduino);
        return -1;
    }

}


#endif // SERIALWRITE_H