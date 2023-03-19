#include "MoreOptionsLayerHook.h"

auto libBase = reinterpret_cast<uintptr_t>(GetModuleHandle("libcocos2d.dll"));

void MoreOptionsLayerHook::LoadHooks() {
    matdash::add_hook<&MoreOptionsLayerHook::MoreOptionsLayerInit>(base + 0x1DE8F0);
}

bool MoreOptionsLayerHook::MoreOptionsLayerInit() {

    if(!matdash::orig<&MoreOptionsLayerHook::MoreOptionsLayerInit>(this)) return false;
    MoreOptionsLayerHook::OptionCheckUpdate();

    this->addToggle("Practice Music", "6000", "Plays the level's song in-sync with your position, instead of the standard practice song.");
    this->addToggle("No Transition", "6001", "Shorterns scene transition time to 0s.");
    this->addToggle("Text Bypass", "6002", "Allows for unlimited text length in text inputs & Lets you input any character in all text inputs.");
    this->addToggle("Hide Attempts", "6003", "Hides the attempt count in-game.");
    this->addToggle("Slider Limit", "6004", "Lets sliders be dragged beyond the visible limit.");
    this->addToggle("Free Window Resize", "6005", "Removes limits in place for window resizing.");
    //this->addToggle("", "0", "");

    return true;
}

void MoreOptionsLayerHook::OptionCheckUpdate() {

    bool practiceMusic = GameManager::sharedState()->getGameVariable("6000");
	bool noTransition = GameManager::sharedState()->getGameVariable("6001");
    bool textByPass = GameManager::sharedState()->getGameVariable("6002");
    bool hideAtts = GameManager::sharedState()->getGameVariable("6003");
    bool sliderLimit = GameManager::sharedState()->getGameVariable("6004");
    bool freewinresize = GameManager::sharedState()->getGameVariable("6005");
    
    if( practiceMusic ) {
        patchMemory(reinterpret_cast<void*>(base + 0x20C925), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
        patchMemory(reinterpret_cast<void*>(base + 0x20D143), {0x90, 0x90});
        patchMemory(reinterpret_cast<void*>(base + 0x20A563), {0x90, 0x90});
        patchMemory(reinterpret_cast<void*>(base + 0x20A595), {0x90, 0x90});
    } else {
        patchMemory(reinterpret_cast<void*>(base + 0x20C925), {0x0f, 0x85, 0xf7, 0x00, 0x00, 0x00});
        patchMemory(reinterpret_cast<void*>(base + 0x20D143), {0x75, 0x41});
        patchMemory(reinterpret_cast<void*>(base + 0x20A563), {0x75, 0x3e});
        patchMemory(reinterpret_cast<void*>(base + 0x20A595), {0x75, 0x0c});
    }

    if( noTransition ) {
        patchMemory(reinterpret_cast<void*>(libBase + 0xA5424), {0x90, 0x90, 0x90, 0x90, 0x90});
    } else {
        patchMemory(reinterpret_cast<void*>(libBase + 0xA5424), {0xF3, 0x0F, 0x10, 0x45, 0x08});
    }

    if( textByPass ) {
        patchMemory(reinterpret_cast<void*>(libBase + 0x21ACB), {0xEB, 0x04});
        patchMemory(reinterpret_cast<void*>(libBase + 0x21A99), {0x90, 0x90});
    } else {
        patchMemory(reinterpret_cast<void*>(libBase + 0x21ACB), {0x7C, 0x04});
        patchMemory(reinterpret_cast<void*>(libBase + 0x21A99), {0x75, 0x04});
    }

    if( hideAtts ) {
        patchMemory(reinterpret_cast<void*>(base + 0x2D83B8), {0x00});
    } else {
        patchMemory(reinterpret_cast<void*>(base + 0x2D83B8), {0x41});
    }

    if( freewinresize ) {
        patchMemory(reinterpret_cast<void*>(libBase + 0x11388B), {0x90, 0x90, 0x90, 0x90, 0x90});
        patchMemory(reinterpret_cast<void*>(libBase + 0x11339D), {0xB9, 0xFF, 0xFF, 0xFF, 0x7F, 0x90, 0x90});
        patchMemory(reinterpret_cast<void*>(libBase + 0x1133C0), {0x48});
        patchMemory(reinterpret_cast<void*>(libBase + 0x1133C6), {0x48});
        patchMemory(reinterpret_cast<void*>(libBase + 0x112536), {0xEB, 0x11, 0x90});
    } else {
        patchMemory(reinterpret_cast<void*>(libBase + 0x11388B), {0xE8, 0xB0, 0xF3, 0xFF, 0xFF});
        patchMemory(reinterpret_cast<void*>(libBase + 0x11339D), {0xE8, 0xEE, 0xF6, 0xFF, 0xFF, 0x8B, 0xC8});
        patchMemory(reinterpret_cast<void*>(libBase + 0x1133C0), {0x50});
        patchMemory(reinterpret_cast<void*>(libBase + 0x1133C6), {0x50});
        patchMemory(reinterpret_cast<void*>(libBase + 0x112536), {0x50, 0x6A, 0x00});
    }

    if ( sliderLimit ) {
        patchMemory(reinterpret_cast<void*>(base + 0x2E5CA), {0xEB});
        patchMemory(reinterpret_cast<void*>(base + 0x2E5F8), {0xEB});
    } else {
        patchMemory(reinterpret_cast<void*>(base + 0x2E5CA), {0x76});
        patchMemory(reinterpret_cast<void*>(base + 0x2E5F8), {0x76});
    }

    //song bypass
    //patchMemory(reinterpret_cast<void*>(base + 0x2CDF44), {0x68, 0x74, 0x74, 0x70, 0x73, 0x3A, 0x2F, 0x2F, 0x61, 0x62, 0x73, 0x6F, 0x6C, 0x6C, 0x6C, 0x75, 0x74, 0x65, 0x2E, 0x63, 0x6F, 0x6D, 0x2F, 0x61, 0x70, 0x69, 0x2F, 0x67, 0x64, 0x5F, 0x73, 0x6F, 0x6E, 0x67, 0x5F, 0x62, 0x79, 0x70, 0x61, 0x73, 0x73, 0x00});
    //patchMemory(reinterpret_cast<void*>(base + 0x2CDF44), {0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x77, 0x77, 0x77, 0x2E, 0x62, 0x6F, 0x6F, 0x6D, 0x6C, 0x69, 0x6E, 0x67, 0x73, 0x2E, 0x63, 0x6F, 0x6D, 0x2F, 0x64, 0x61, 0x74, 0x61, 0x62, 0x61, 0x73, 0x65, 0x2F, 0x67, 0x65, 0x74, 0x47, 0x4A, 0x53, 0x6F, 0x6E, 0x67, 0x49, 0x6E, 0x66, 0x6F, 0x2E, 0x70, 0x68, 0x70, 0x00});

}

void MoreOptionsLayerHook::patchMemory(void* patchLoc, std::vector<uint8_t> bytes) {
    DWORD old_prot;
    VirtualProtect(patchLoc, bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot);
    memcpy(patchLoc, bytes.data(), bytes.size());
    VirtualProtect(patchLoc, bytes.size(), old_prot, &old_prot);
}