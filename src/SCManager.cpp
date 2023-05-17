#include "SCManager.h"
#include "SCToolBox.h"
#include "SCOptionsLayer.h"

auto libBase = reinterpret_cast<uintptr_t>(GetModuleHandle("libcocos2d.dll"));
bool StartUpChecked = false;

void SCManager::StartUpCheck()
{
    if(StartUpChecked) return;

    StartUpChecked = true;
    bool practiceMusic = SCManager::getSCModVariable("6000");
    bool noTransition = SCManager::getSCModVariable("6001");
    bool textByPass = SCManager::getSCModVariable("6002");
    bool hideAtts = SCManager::getSCModVariable("6003");
    bool sliderLimit = SCManager::getSCModVariable("6004");
    bool freewinresize = SCManager::getSCModVariable("6005");

    if(practiceMusic) enablePatch("6000");
    if(noTransition) enablePatch("6001");
    if(textByPass) enablePatch("6002");
    if(hideAtts) enablePatch("6003");
    if(sliderLimit) enablePatch("6004");
    if(freewinresize) enablePatch("6005");
}

void SCManager::enablePatch(const char* optionKey)
{
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
    if(strcmp(optionKey, "6009") == 0){
        return SCOptionsLayer::setSongFolder();
    }
}

void SCManager::disablePatch(const char* optionKey)
{ 
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
// save file stuff

std::filesystem::path getSaveFilePath() {
    const auto path = CCFileUtils::sharedFileUtils()->getWritablePath();
    return std::filesystem::path(path) / "SCModManager.dat"; //xD
}

inline std::pair<std::string, std::string> splitKey(const std::string str, char split) {
	const auto n = str.find(split);
	return { str.substr(0, n), str.substr(n + 1) };
}

void createSaveFile()
{
    std::cout << "generate savefile" << std::endl;
    const auto path = getSaveFilePath();
    std::ofstream file(path);
}

std::vector<std::string> getSaveFile()
{
    const auto path = getSaveFilePath();
    if (!std::filesystem::exists(path)) createSaveFile();
    std::ifstream file(path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

void saveCfgFile(std::vector<std::string> file)
{
    const auto path = getSaveFilePath();
    std::ofstream savefile(path);
    size_t pos = 0;
    while(pos < file.size()) {
        savefile << file[pos] << "\n";
        pos++;
    }
}

void SCManager::setSCModVariable(std::string key, bool value)
{
    std::string tostr = value ? "true" : "false";
    SCManager::setSCModString(key, tostr);
}

void SCManager::setSCModString(std::string key, std::string value)
{
    std::vector<std::string> saveFile = getSaveFile();
    size_t pos = 0;
    bool isfound = false;
    while (pos < saveFile.size()) {
        const auto [orikey, valuex] = splitKey(saveFile[pos], '=');
        if (key == orikey) {
            isfound = true;
            saveFile[pos] = key + "=" + value;
        }
        pos++;
    }

    if(!isfound) saveFile.push_back(key + "=" + value);
    
    saveCfgFile(saveFile);
}

bool SCManager::getSCModVariable(std::string key)
{
    std::vector<std::string> saveFile = getSaveFile();
    size_t pos = 0;
    while (pos < saveFile.size()) {
        const auto [orikey, value] = splitKey(saveFile[pos], '=');
        if (key == orikey) {
            return value == "true";
        }
        pos++;
    }
    return false;
}

std::string SCManager::getSCModString(std::string key)
{
    std::vector<std::string> saveFile = getSaveFile();
    size_t pos = 0;
    while (pos < saveFile.size()) {
        const auto [orikey, value] = splitKey(saveFile[pos], '=');
        if (key == orikey) {
            return value;
        }
        pos++;
    }
    return false;
}