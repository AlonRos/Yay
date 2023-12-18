#pragma once
#include <windows.h>
#include <cstdint>

#define IOCTL_MAP_MEMORY 0x80112044
#define IOCTL_READ_MSR_DIRECTIO 0x80112060

typedef unsigned __int64 QWORD;

class CommWithDriverManager {

private:

	HANDLE device;
	struct MapPhysicalMemoryInput;
	struct MapPhysicalMemoryOutput;

public:

	HANDLE initializeDevice(LPCWSTR deviceName);

	BOOL mapPhysicalAddressToVirtual(PVOID physicalAddress, DWORD numberOfBytes, PVOID* toStore);

	BOOL readMSR(DWORD registerAddress, QWORD* store);

	BOOL writeMSR(HANDLE device, DWORD registerAddress, QWORD value);

};

