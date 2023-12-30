#pragma once
#include <windows.h>
#include <cstdint>

#define IOCTL_READ_MEMORY  0xC3506104
#define IOCTL_WRITE_MEMORY 0xC350A108

#define IOCTL_READ_MSR 0xC3502084
#define IOCTL_WRITE_MSR 0xC3502088

#define memberSize(type, member) sizeof(((type *)0)->member)

#define readStructMemberFromPhysicalMemory(structPhysicalAddress, type, member, outputBuffer) \
readPhysicalMemory((BYTE*)structPhysicalAddress + offsetof(type, member), 1, memberSize(type, member), outputBuffer)

#define writeStructMemberToPhysicalMemory(structPhysicalAddress, type, member, bufferToWrite) \
writePhysicalMemory((BYTE*)structPhysicalAddress + offsetof(type, member), 1, memberSize(type, member), bufferToWrite)

#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))

typedef unsigned __int64 QWORD;


class CommWithDriverManager {

private:

	HANDLE device;
	struct RWPhysicalMemoryInput;
	struct writeMSRInput;

public:

	HANDLE initializeDevice(LPCWSTR deviceName);

	// chunkSize must be one of {1, 2, 4} (bytes)
	BOOL readPhysicalMemory(PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID outputBuffer);

	// chunkSize must be one of {1, 2, 4} (bytes)
	BOOL writePhysicalMemory(PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID bufferToWrite);

	BOOL readMSR(DWORD registerAddress, QWORD* store);

	BOOL writeMSR(DWORD registerAddress, QWORD value);

};

