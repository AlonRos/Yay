#pragma once
#include <windows.h>

#define IOCTL_READ  0xC3506104
#define IOCTL_WRITE 0xC350A108

typedef unsigned __int64 QWORD;

// chunkSize must be one of {1, 2, 4} (bytes)
BOOL readPhysicalMemory(HANDLE device, PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID outputBuffer);

// chunkSize must be one of {1, 2, 4} (bytes)
BOOL writePhysicalMemory(HANDLE device, PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID bufferToWrite);

