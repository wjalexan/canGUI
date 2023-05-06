//#include <iostream>
//#include <Windows.h>
//#include <string>
//#include "mainwindow.h"
////#include "ui_mainwindow.h"


//char checkChar(char inpt){
//    switch (inpt){
//    case '^':
//        return 'b'; // searches for starting character
//        break;

//    case '*':
//        return 'f'; // searces for termination character
//        break;

//    case ',':
//        return 's'; // searches for separation character
//        break;

//    default:
//        if ((int(inpt) >= 64 && int(inpt) <= 90) || (int(inpt) >= 48 && int(inpt) <= 57)) {
//            return 'v'; // searches for valid data bit
//        }
//        else {
//            return 'n';
//        }
//    }
//}

//int IDlen(std::string can, int start){
//    for (int i = 1; i < 255-start; i++){
//        if (checkChar(can[start + i]) == 's'){
//            return i;
//            break;
//        }
//    }
//    return -1;
//}


//int findEnd(char data[255]){
//    for (int j = 255; j > 0; j--){
//        if (checkChar(data[j]) == 'f'){
//            return j;
//            break;
//        }
//    }
//}
