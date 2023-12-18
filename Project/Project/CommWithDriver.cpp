#include <windows.h>
#include "CommWithDriver.h"
#include "Structures.h"
#include <iostream>

HANDLE CommWithDriverManager::initializeDevice(LPCWSTR deviceName) {
	device = CreateFileW(deviceName, GENERIC_READ | GENERIC_WRITE, NULL, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
	return device;
}

BOOL CommWithDriverManager::readMSR(DWORD registerAddress, QWORD* store) {
	return DeviceIoControl(device, IOCTL_READ_MSR_DIRECTIO, &registerAddress, 4, store, 8,NULL, NULL);

}

BOOL CommWithDriverManager::mapPhysicalAddressToVirtual(PVOID physicalAddress, DWORD numberOfBytes, PVOID* toStore) {
	MapPhysicalMemoryInput* input = new MapPhysicalMemoryInput{ numberOfBytes, physicalAddress };
	MapPhysicalMemoryOutput* output = (MapPhysicalMemoryOutput*)input;

	BOOL b = DeviceIoControl(
		device, IOCTL_MAP_MEMORY,
		input, sizeof(MapPhysicalMemoryInput),
		output, sizeof(MapPhysicalMemoryOutput),
		NULL, NULL
	);
	
	*toStore = output->baseAddress;

	return b;
}