#include "GDGameSoundManager.h"
#include "SCManager.h"
#include <vector>
#include <string>

void GDGameSoundManager::Hook()
{
    matdash::add_hook<&GDGameSoundManager::playBGMusic>(base + 0x252b0);
}

void GDGameSoundManager::playBGMusic(bool idk, bool idk2, std::string path)
{
    if(SCManager::getSCModVariable("6009")){
        int posInit = 0;
        int posFound = 0;
        std::string splitted;
        std::vector<std::string> results;
        while(posFound >= 0){
            posFound = path.find('\\', posInit);
            splitted = path.substr(posInit, posFound - posInit);
            posInit = posFound + 1;
            results.push_back(splitted);
        }
        if(results.size() > 1){
            auto custompath = SCManager::getSCModString("6010") + '\\' + results[results.size() - 1];
            std::cout << custompath << std::endl;

            matdash::orig<&GDGameSoundManager::playBGMusic>(this, idk, idk2, custompath);
        } else {
            matdash::orig<&GDGameSoundManager::playBGMusic>(this, idk, idk2, path);
        }
    } else {
        matdash::orig<&GDGameSoundManager::playBGMusic>(this, idk, idk2, path);
    }

    if (FMODAudioEngine::sharedEngine()->isBackgroundMusicPlaying(std::string("menuLoop.mp3"))) {
        if (SCManager::getSCModVariable("6011")) {
            GameSoundManager::sharedState()->stopBackgroundMusic();
        }
    }
}