#include <windows.h>
#include "ReadWrite.h"

// chunkSize must be one of {1, 2, 4} (bytes)
BOOL readPhysicalMemory(HANDLE device, PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID outputBuffer) {
    BYTE* inputBuffer = (BYTE*)malloc(16);

    memcpy(inputBuffer, &physicalAddress, sizeof(QWORD));
    memcpy(inputBuffer + 8, &chunkSize, sizeof(DWORD));
    memcpy(inputBuffer + 12, &amountOfChunks, sizeof(DWORD));

    return DeviceIoControl(device, IOCTL_READ_MEMORY, inputBuffer, 16, outputBuffer, chunkSize * amountOfChunks, NULL, NULL);
}

// chunkSize must be one of {1, 2, 4} (bytes)
BOOL writePhysicalMemory(HANDLE device, PVOID physicalAddress, DWORD chunkSize, DWORD amountOfChunks, PVOID bufferToWrite) {
    int amountBytesToWrite = chunkSize * amountOfChunks;

    BYTE* inputBuffer = (BYTE*)malloc(16 + amountBytesToWrite);

    memcpy(inputBuffer, &physicalAddress, sizeof(QWORD));
    memcpy(inputBuffer + 8, &chunkSize, sizeof(DWORD));
    memcpy(inputBuffer + 12, &amountOfChunks, sizeof(DWORD));
    memcpy(inputBuffer + 16, bufferToWrite, amountBytesToWrite);


    return DeviceIoControl(device, IOCTL_WRITE_MEMORY, inputBuffer, 16 + amountBytesToWrite, NULL, NULL, NULL, NULL);
}

BOOL readMSR(HANDLE device, DWORD registerAddress, QWORD* store) {
    return DeviceIoControl(device, IOCTL_READ_MSR, &registerAddress, 4, store, 8, NULL, NULL);
}

BOOL writeMSR(HANDLE device, DWORD registerAddress, QWORD value) {
    BYTE* inputBuffer = (BYTE*)malloc(12);
    memcpy(inputBuffer, &registerAddress, sizeof(DWORD));
    memcpy(inputBuffer + 4, &value, sizeof(QWORD));

    return DeviceIoControl(device, IOCTL_WRITE_MSR, inputBuffer, 12, NULL, NULL, NULL, NULL);
}
