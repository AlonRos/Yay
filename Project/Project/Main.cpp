#include <windows.h>
#include <iostream>
#include "ReadWrite.h"

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