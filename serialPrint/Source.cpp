#include <iostream>
#include <Windows.h>
#include <string>
#include "serialRead.h"
#include "serialWrite.h"

int main() {
	serialWrite(L"COM3", "S");
	//serialRead(L"COM3");
	return 0;
}