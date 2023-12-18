#pragma once
#include <windows.h>
#include <cstdint>

#define IOCTL_MAP_MEMORY   0x80002000
#define IOCTL_UNMAP_MEMORY 0x80002004

#define IOCTL_READ_MSR  0x80002030
#define IOCTL_WRITE_MSR 0x80002034


#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))

typedef unsigned __int64 QWORD;

class CommWithDriverManager {

private:

	HANDLE device;
	struct MapPhysicalMemoryInput;
	struct readMSRSBuffer;
	struct writeMSRInput;

public:

	HANDLE initializeDevice(LPCWSTR deviceName);

	BOOL mapPhysicalAddressToVirtual(PVOID physicalAddress, DWORD numberOfBytes, PVOID* toStore);

	BOOL unmapPhysicalAddressToVirtual(PVOID physicalAddress);

	BOOL readMSR(DWORD registerAddress, QWORD* store);

	BOOL writeDwordToMSR(DWORD registerAddress, DWORD value);

};

