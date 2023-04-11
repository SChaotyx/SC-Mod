#include "GDGameSoundManager.h"

void GDGameSoundManager::Hook()
{
    matdash::add_hook<&GDGameSoundManager::playBGMusic>(base + 0x252b0);
}

void GDGameSoundManager::playBGMusic(bool idk, bool idk2, std::string path)
{
    matdash::orig<&GDGameSoundManager::playBGMusic>(this, idk, idk2, path);

    if (FMODAudioEngine::sharedEngine()->isBackgroundMusicPlaying(std::string("menuLoop.mp3"))) {
        if (GameManager::sharedState()->getGameVariable("0122")) {
            GameSoundManager::sharedState()->stopBackgroundMusic();
        }
    }
}