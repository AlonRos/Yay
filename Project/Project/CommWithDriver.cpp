#include <windows.h>
#include "CommWithDriver.h"
#include "Structures.h"
#include <iostream>

HANDLE CommWithDriverManager::initializeDevice(LPCWSTR deviceName) {
	device = CreateFileW(deviceName, GENERIC_READ | GENERIC_WRITE, NULL, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
	return device;
}

BOOL CommWithDriverManager::mapPhysicalAddressToVirtual(PVOID physicalAddress, DWORD numberOfBytes, PVOID* toStore) {
	MapPhysicalMemoryInput* input = new MapPhysicalMemoryInput{ physicalAddress, numberOfBytes };

	return DeviceIoControl(device, IOCTL_MAP_MEMORY, input, sizeof(MapPhysicalMemoryInput), toStore, sizeof(PVOID), NULL, NULL);
}

BOOL CommWithDriverManager::unmapPhysicalAddressToVirtual(PVOID physicalAddress) {

	return DeviceIoControl(device, IOCTL_UNMAP_MEMORY, &physicalAddress, sizeof(PVOID), NULL, NULL, NULL, NULL);
}

BOOL CommWithDriverManager::readMSR(DWORD registerAddress, QWORD* store) {
	readMSRSBuffer* bufferptr = new readMSRSBuffer{ registerAddress };

	BOOL b = DeviceIoControl(device, IOCTL_READ_MSR, bufferptr, sizeof(*bufferptr), bufferptr, sizeof(*bufferptr), NULL, NULL);

	*(DWORD*)store = bufferptr->lowDword;
	*((DWORD*)store + 1) = bufferptr->highDword;

	return b;
}

BOOL CommWithDriverManager::writeMSR(DWORD registerAddress, QWORD value) {
	int x = ~15;

}