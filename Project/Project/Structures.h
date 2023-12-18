#pragma once
#include <windows.h>
#include  <cstdint>
#include "CommWithDriver.h"

typedef unsigned __int64 QWORD;

struct CommWithDriverManager::MapPhysicalMemoryInput {
    uint32_t : 32;

    DWORD numberOfBytes;

    PVOID physicalAddress;

    uint64_t : 64;

    const char flag = 1;

};


struct CommWithDriverManager::MapPhysicalMemoryOutput {
    uint32_t : 32;

    uint32_t : 32;

    PVOID physicalAddress;

    PVOID baseAddress;

    uint8_t : 8;

};
