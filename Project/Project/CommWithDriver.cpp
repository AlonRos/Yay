#include <windows.h>
#include "CommWithDriver.h"
#include "Structures.h"
#include "PackedStructures.h"
#include <iostream>

HANDLE CommWithDriverManager::initializeDevice(LPCWSTR deviceName) {
	device = CreateFileW(deviceName, GENERIC_READ | GENERIC_WRITE, NULL, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
	return device;
}

BOOL CommWithDriverManager::readPhysicalMemory(PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID outputBuffer) {
	RWPhysicalMemoryInput* inputBuffer = new RWPhysicalMemoryInput{ physicalAddress, chunkSize, amountOfChunks };

	return DeviceIoControl(device, IOCTL_READ_MEMORY, inputBuffer, 16, outputBuffer, chunkSize * amountOfChunks, NULL, NULL);
}


BOOL CommWithDriverManager::writePhysicalMemory(PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID bufferToWrite) {

	int amountBytesToWrite = chunkSize * amountOfChunks;

	BYTE* inputBuffer = (BYTE*)malloc(16 + amountBytesToWrite);

	*(RWPhysicalMemoryInput*)inputBuffer = { physicalAddress, chunkSize, amountOfChunks };

	memcpy(inputBuffer + 16, bufferToWrite, amountBytesToWrite);

	return DeviceIoControl(device, IOCTL_WRITE_MEMORY, inputBuffer, 16 + amountBytesToWrite, NULL, NULL, NULL, NULL);
}

BOOL CommWithDriverManager::readMSR(DWORD registerAddress, QWORD* store) {
	return DeviceIoControl(device, IOCTL_READ_MSR, &registerAddress, 4, store, 8, NULL, NULL);
	
}

BOOL CommWithDriverManager::writeMSR(DWORD registerAddress, QWORD value) {
	BYTE* inputBuffer = (BYTE*)malloc(12);
	memcpy(inputBuffer, &registerAddress, sizeof(DWORD));
	memcpy(inputBuffer + 4, &value, sizeof(QWORD));

	return DeviceIoControl(device, IOCTL_WRITE_MSR, inputBuffer, 12, NULL, NULL, NULL, NULL);
}