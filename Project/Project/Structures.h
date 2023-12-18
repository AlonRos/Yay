#pragma once
#include <windows.h>
#include  <cstdint>
#include "CommWithDriver.h"

typedef unsigned __int64 QWORD;


struct CommWithDriverManager::MapPhysicalMemoryInput {
    PVOID physicalAddress; 

    DWORD numberOfBytes;

    int32_t : 32;

};

struct CommWithDriverManager::readMSRSBuffer {
    DWORD registerAddress;

    DWORD highDword;

    DWORD lowDword;

};

struct CommWithDriverManager::writeMSRInput {
    DWORD registerAddress;

    int32_t : 32;

    DWORD value;
};