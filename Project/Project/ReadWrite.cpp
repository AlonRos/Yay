#include <windows.h>
#include "ReadWrite.h"

// chunkSize must be one of {1, 2, 4} (bytes)
BOOL readPhysicalMemory(HANDLE device, PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID outputBuffer) {
    BYTE* inputBuffer = (BYTE*)malloc(16);

    memmove(inputBuffer, &physicalAddress, sizeof(QWORD));
    memmove(inputBuffer + 8, &chunkSize, sizeof(DWORD));
    memmove(inputBuffer + 12, &amountOfChunks, sizeof(DWORD));

    return DeviceIoControl(device, IOCTL_READ, inputBuffer, 16, outputBuffer, chunkSize * amountOfChunks, NULL, NULL);
}

// chunkSize must be one of {1, 2, 4} (bytes)
BOOL writePhysicalMemory(HANDLE device, PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID bufferToWrite) {
    int amountBytesToWrite = chunkSize * amountOfChunks;

    BYTE* inputBuffer = (BYTE*)malloc(16 + amountBytesToWrite);

    memmove(inputBuffer, &physicalAddress, sizeof(QWORD));
    memmove(inputBuffer + 8, &chunkSize, sizeof(DWORD));
    memmove(inputBuffer + 12, &amountOfChunks, sizeof(DWORD));
    memmove(inputBuffer + 16, bufferToWrite, amountBytesToWrite);


    return DeviceIoControl(device, IOCTL_WRITE, inputBuffer, 16 + amountBytesToWrite, NULL, NULL, NULL, NULL);
}
