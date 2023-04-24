#include <iostream>
#include <Windows.h>
#include <string>
//#include "mainwindow.h"

#ifndef CHECKCHAR_H
#define CHECKCHAR_H


char checkChar(char inpt){
    switch (inpt){
    case '^':
        return 's'; // searches for starting character
        break;

    case '*':
        return 'f'; // searces for termination character
        break;

    default:
        if ((int(inpt) >= 64 && int(inpt) <= 90) || (int(inpt) >= 48 && int(inpt) <= 57)) {
            return 'v'; // searches for valid data bit
        }
        else {
            return 'n';
        }
    }
}


#endif // CHECKCHAR_H
