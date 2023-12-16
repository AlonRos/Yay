#pragma once
#include <windows.h>

#define IOCTL_READ_MEMORY  0xC3506104
#define IOCTL_WRITE_MEMORY 0xC350A108

#define IOCTL_READ_MSR 0xC3502084
#define IOCTL_WRITE_MSR 0xC3502088

#define memberSize(type, member) sizeof(((type *)0)->member)

#define readStructMemberFromPhysicalMemory(device, structPhysicalAddress, type, member, outputBuffer) \
readPhysicalMemory(device, (BYTE*)structPhysicalAddress + offsetof(type, member), 1, memberSize(type, member), outputBuffer)

#define writeStructMemberToPhysicalMemory(device, structPhysicalAddress, type, member, bufferToWrite) \
writePhysicalMemory(device, (BYTE*)structPhysicalAddress + offsetof(type, member), 1, memberSize(type, member), bufferToWrite)

typedef unsigned __int64 QWORD;

// chunkSize must be one of {1, 2, 4} (bytes)
BOOL readPhysicalMemory(HANDLE device, PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID outputBuffer);

// chunkSize must be one of {1, 2, 4} (bytes)
BOOL writePhysicalMemory(HANDLE device, PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID bufferToWrite);

BOOL readMSR(HANDLE device, DWORD registerAddress, QWORD* store);

BOOL writeMSR(HANDLE device, DWORD registerAddress, QWORD value);