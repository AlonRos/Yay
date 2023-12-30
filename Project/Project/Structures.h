#pragma once
#include <windows.h>
#include <cstdint>
#include "CommWithDriver.h"

typedef unsigned __int64 QWORD;


struct CommWithDriverManager::RWPhysicalMemoryInput {
    PVOID physicalAddress; 

    DWORD chunkSize;

    DWORD amountOfChunks;

};

