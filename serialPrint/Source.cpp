#include <iostream>
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>
#include "serialRead.h"
#include "serialWrite.h"

int main() {
	//serialWrite(L"COM4", "S");
	//std::this_thread::sleep_for(std::chrono::seconds(10)); // pause operation for 1 second
	serialRead(L"COM4");
	return 0;
}