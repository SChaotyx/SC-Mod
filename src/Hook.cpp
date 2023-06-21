#include "Hooks.h"

#include "GDMenuLayer.h"
#include "GDEditLevelLayer.h"
#include "GDPauseLayer.h"
#include "GDPlayLayer.h"
#include "GDEndLevelLayer.h"
#include "GDOptionsLayer.h"
#include "GDLevelInfoLayer.h"
#include "GDGameSoundManager.h"

#include "SCManager.h"
#include "SCToolsLayer.h"
#include "SCToolBox.h"

static auto libcocos = GetModuleHandleA("libcocos2d.dll");
static auto fmodBase = GetModuleHandleA("fmod.dll");

void CCKeyboardDispatcher_dispatchKeyboardMSG(CCKeyboardDispatcher* self, int key, bool down) {
    if (down && !SCManager::getSCModVariable("Opt_disableKeybinds")) {
        if(auto play_layer = GameManager::sharedState()->getPlayLayer()){
            if(!play_layer->m_hasCompletedLevel && !play_layer->m_bIsPaused) {
                if(play_layer->get()->m_level->m_eLevelType == kGJLevelTypeEditor){
                    if (key == 'N') {
                        SCToolsLayer::noclipToggler();
                    } else if (key == 'M') {
                        SCToolBox::setLevelSpeed(1);
                    } else if (key == 188) { //,
                        SCToolsLayer::decLevelSpeed(true);
                    } else if (key == 190) { //.
                        SCToolsLayer::decLevelSpeed(false);
                    }
                }
                if(key == 'A') reinterpret_cast<void(__thiscall*)(PlayLayer*)>(base + 0x20BF00)(play_layer); //reset level
            }
        }
    }
    matdash::orig<&CCKeyboardDispatcher_dispatchKeyboardMSG>(self, key, down);
}
void CCScheduler_update(CCScheduler* self, float dt) {
    matdash::orig<&CCScheduler_update, matdash::Thiscall>(self, dt);
}

void Hooks::Load()
{
    GDMenuLayer::Hook();
    GDPlayLayer::Hook();
    GDPauseLayer::Hook();
    GDEndLevelLayer::Hook();
    GDEditLevelLayer::Hook();
    GDLevelInfoLayer::Hook();
    GDOptionsLayer::Hook();
    GDGameSoundManager::Hook();

    // from https://github.com/matcool/ReplayBot
    matdash::add_hook<&CCKeyboardDispatcher_dispatchKeyboardMSG>
        (GetProcAddress(libcocos, "?dispatchKeyboardMSG@CCKeyboardDispatcher@cocos2d@@QAE_NW4enumKeyCodes@2@_N@Z"));

    // matdash::add_hook<&CCScheduler_update, matdash::Thiscall>
    //     (GetProcAddress(libcocos, "?update@CCScheduler@cocos2d@@UAEXM@Z"));

    SCToolBox::FMOD_Channel_setPitch = reinterpret_cast<decltype(SCToolBox::FMOD_Channel_setPitch)>
        (GetProcAddress(fmodBase, "?setPitch@ChannelControl@FMOD@@QAG?AW4FMOD_RESULT@@M@Z"));
}