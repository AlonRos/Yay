#pragma once
#include <windows.h>
#include <cstdint>
#include "CommWithDriver.h"

typedef unsigned __int64 QWORD;

#pragma pack(push, 1)
struct CommWithDriverManager::writeMSRInput {
    DWORD registerAddress;

    QWORD value;
};
#pragma pack(pop)