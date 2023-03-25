#include "Utils.h"

void Utils::patchMemory(void* patchLoc, std::vector<uint8_t> bytes) {
    DWORD old_prot;
    VirtualProtect(patchLoc, bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot);
    memcpy(patchLoc, bytes.data(), bytes.size());
    VirtualProtect(patchLoc, bytes.size(), old_prot, &old_prot);
    //std::cout << "Applied Patch to " << patchLoc << std::endl;
}