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
    //this->addToggle("Hide Attempts", "6003", "Hides the attempt count in-game.");
    //this->addToggle("Free Window Resize", "6004", "Removes limits in place for window resizing.");
    
    return true;
}

void MoreOptionsLayerHook::OptionCheckUpdate() {

    bool practiceMusic = GameManager::sharedState()->getGameVariable("6000");
	bool noTransition = GameManager::sharedState()->getGameVariable("6001");
    bool textByPass = GameManager::sharedState()->getGameVariable("6002");
    //bool hideAtts = GameManager::sharedState()->getGameVariable("6003");
    //bool freewinresize = GameManager::sharedState()->getGameVariable("6004");
    
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
/*
    if( hideAtts ) {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x2D83B8), "\x00\x00", 2, NULL);
    } else {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x2D83B8), "\x41\x00", 2, NULL);
    }

    if( freewinresize ) {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x11388B), "\x90\x90\x90\x90\x90", 5, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x11339D), "\xB9\xFF\xFF\xFF\x7F\x90\x90", 7, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x1133C0), "\x48", 1, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x1133C6), "\x48", 1, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x112536), "\xEB\x11\x90", 3, NULL);
    } else {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x11388B), "\xE8\xB0\xF3\xFF\xFF", 5, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x11339D), "\xE8\xEE\xF6\xFF\xFF\x8B\xC8", 7, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x1133C0), "\x50", 1, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x1133C6), "\x50", 1, NULL);
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0x112536), "\x50\x6A\x00", 3, NULL);
    }
*/
   //level kick anticheat (for recording only)
   // WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x202AAA), "\xEB\x2E", 2, NULL);
   /*
   {
	  "name": "Free Window Resize",
	  "desc": "Removes limits in place for window resizing.",
	  "opcodes": [
	    {"addr": "0x11388B", "lib": "libcocos2d.dll", "on": "90 90 90 90 90", "off": "E8 B0 F3 FF FF"},
		{"addr": "0x11339D", "lib": "libcocos2d.dll", "on": "B9 FF FF FF 7F 90 90", "off": "E8 EE F6 FF FF 8B C8"},
		{"addr": "0x1133C0", "lib": "libcocos2d.dll", "on": "48", "off": "50"},
		{"addr": "0x1133C6", "lib": "libcocos2d.dll", "on": "48", "off": "50"},
		{"addr": "0x112536", "lib": "libcocos2d.dll", "on": "EB 11 90", "off": "50 6A 00"}
	  ]
	},
    {
	  "name": "Hide Attempts",
	  "desc": "Hides the attempt count in-game.",
	  "opcodes": [
	    {"addr": "0x2D83B8", "on": "00", "off": "41"}
	  ]
	},
   */
}