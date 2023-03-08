#include <iostream>
#include <string>
#include <windows.h>
#include "serialwrite.h"

int main() {
	serialWrite(L"COM3", "a");
	return 0;
}