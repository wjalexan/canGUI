#include <iostream>
#include <windows.h>
#include <string>
#include "serialRead.h"
#include "serialWrite.h"

int main() {
	//serialWrite(L"COM3", "h");
	serialRead(L"COM3");
	return 0;
}