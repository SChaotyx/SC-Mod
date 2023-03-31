#include "SCManager.h"
#include "SCToolBox.h"

auto libBase = reinterpret_cast<uintptr_t>(GetModuleHandle("libcocos2d.dll"));
bool StartUpChecked = false;

void SCManager::StartUpCheck(){
    if(StartUpChecked) return;

    StartUpChecked = true;
    bool practiceMusic = GameManager::sharedState()->getGameVariable("6000");
    bool noTransition = GameManager::sharedState()->getGameVariable("6001");
    bool textByPass = GameManager::sharedState()->getGameVariable("6002");
    bool hideAtts = GameManager::sharedState()->getGameVariable("6003");
    bool sliderLimit = GameManager::sharedState()->getGameVariable("6004");
    bool freewinresize = GameManager::sharedState()->getGameVariable("6005");

    if(practiceMusic) enablePatch("6000");
    if(noTransition) enablePatch("6001");
    if(textByPass) enablePatch("6002");
    if(hideAtts) enablePatch("6003");
    if(sliderLimit) enablePatch("6004");
    if(freewinresize) enablePatch("6005");

}

void SCManager::enablePatch(const char* optionKey){

    if(strcmp(optionKey, "6000") == 0){  //practice music
        std::cout << "Enable Practice music" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20C925), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20D143), {0x90, 0x90});
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20A563), {0x90, 0x90});
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20A595), {0x90, 0x90});
        return;
    }
    if(strcmp(optionKey, "6001") == 0){  //no transition
        std::cout << "Enable No transition" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0xA5424), {0x90, 0x90, 0x90, 0x90, 0x90});
        return;
    }
    if(strcmp(optionKey, "6002") == 0){  //text bypass
        std::cout << "Enable Text bypass" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x21ACB), {0xEB, 0x04});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x21A99), {0x90, 0x90});
        return;
    }
    if(strcmp(optionKey, "6003") == 0){  //hide attempts
        std::cout << "Enable Hide attempts" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x2D83B8), {0x00});
        return;
    }
    if(strcmp(optionKey, "6004") == 0){ //slide limit
        std::cout << "Enable Slider limit" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x2E5CA), {0xEB});
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x2E5F8), {0xEB});
        return;
    }
    if(strcmp(optionKey, "6005") == 0){  // free window resize
        std::cout << "Enable Free window resize" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x11388B), {0x90, 0x90, 0x90, 0x90, 0x90});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x11339D), {0xB9, 0xFF, 0xFF, 0xFF, 0x7F, 0x90, 0x90});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x1133C0), {0x48});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x1133C6), {0x48});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x112536), {0xEB, 0x11, 0x90});
        return;
    }
}

void SCManager::disablePatch(const char* optionKey){ 
    if(strcmp(optionKey, "6000") == 0){  //practice music
        std::cout << "Disable Practice music" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20C925), {0x0f, 0x85, 0xf7, 0x00, 0x00, 0x00});
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20D143), {0x75, 0x41});
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20A563), {0x75, 0x3e});
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20A595), {0x75, 0x0c});
        return;
    }
    if(strcmp(optionKey, "6001") == 0){  //no transition
        std::cout << "Disable No transition" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0xA5424), {0xF3, 0x0F, 0x10, 0x45, 0x08});
        return;
    }
    if(strcmp(optionKey, "6002") == 0){  //text bypass
        std::cout << "Disable Text bypass" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x21ACB), {0x7C, 0x04});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x21A99), {0x75, 0x04});
        return;
    }
    if(strcmp(optionKey, "6003") == 0){  //hide attempts
        std::cout << "Disable Hide attempts" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x2D83B8), {0x41});
        return;
    }
    if(strcmp(optionKey, "6004") == 0){ //slide limit
        std::cout << "Disable Slider limit" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x2E5CA), {0x76});
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x2E5F8), {0x76});
        return;
    }
    if(strcmp(optionKey, "6005") == 0){  // free window resize
        std::cout << "Disable Free window resize" << std::endl;
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x11388B), {0xE8, 0xB0, 0xF3, 0xFF, 0xFF});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x11339D), {0xE8, 0xEE, 0xF6, 0xFF, 0xFF, 0x8B, 0xC8});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x1133C0), {0x50});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x1133C6), {0x50});
        SCToolBox::patchMemory(reinterpret_cast<void*>(libBase + 0x112536), {0x50, 0x6A, 0x00});
        return;
    }
}

 //song bypass
    //SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x2CDF44), {0x68, 0x74, 0x74, 0x70, 0x73, 0x3A, 0x2F, 0x2F, 0x61, 0x62, 0x73, 0x6F, 0x6C, 0x6C, 0x6C, 0x75, 0x74, 0x65, 0x2E, 0x63, 0x6F, 0x6D, 0x2F, 0x61, 0x70, 0x69, 0x2F, 0x67, 0x64, 0x5F, 0x73, 0x6F, 0x6E, 0x67, 0x5F, 0x62, 0x79, 0x70, 0x61, 0x73, 0x73, 0x00});
    //SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x2CDF44), {0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x77, 0x77, 0x77, 0x2E, 0x62, 0x6F, 0x6F, 0x6D, 0x6C, 0x69, 0x6E, 0x67, 0x73, 0x2E, 0x63, 0x6F, 0x6D, 0x2F, 0x64, 0x61, 0x74, 0x61, 0x62, 0x61, 0x73, 0x65, 0x2F, 0x67, 0x65, 0x74, 0x47, 0x4A, 0x53, 0x6F, 0x6E, 0x67, 0x49, 0x6E, 0x66, 0x6F, 0x2E, 0x70, 0x68, 0x70, 0x00});