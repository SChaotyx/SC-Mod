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
    
    return true;
}

void MoreOptionsLayerHook::OptionCheckUpdate() {

    bool practiceMusic = GameManager::sharedState()->getGameVariable("6000");
	bool noTransition = GameManager::sharedState()->getGameVariable("6001");
    bool textByPass = GameManager::sharedState()->getGameVariable("6002");
    
    if( practiceMusic ) {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20C925), "\x90\x90\x90\x90\x90\x90", 6, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20D143), "\x90\x90", 2, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20A563), "\x90\x90", 2, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20A595), "\x90\x90", 2, NULL);
    } else {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20C925), "\x0f\x85\xf7\x00\x00\x00", 6, NULL);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20D143), "\x75\x41", 2, NULL);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20A563), "\x75\x3e", 2, NULL);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20A595), "\x75\x0c", 2, NULL);
    }

    if( noTransition ) {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0xA5424), "\x90\x90\x90\x90\x90", 5, NULL);
    } else {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0xA5424), "\xF3\x0F\x10\x45\x08", 5, NULL);
    }

    if( textByPass ) {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x21ACB), "\xEB\x04", 2, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x21A99), "\x90\x90", 2, NULL);
    } else {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x21ACB), "\x7C\x04", 2, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x21A99), "\x75\x04", 2, NULL);
    }
}