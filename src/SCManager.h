#pragma once

#include <filesystem>
#include <fstream>

namespace SCManager
{
    void StartUpCheck();
    void enablePatch(const char*);
    void disablePatch(const char*);
    //savefile stuff
    void setSCModVariable(std::string, bool);
    void setSCModString(std::string, std::string);
    bool getSCModVariable(std::string);
    std::string getSCModString(std::string);
};