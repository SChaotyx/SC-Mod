#include "Hooks.h"

#include "GDMenuLayer.h"
//#include "GDMoreOptionsLayer.h"
#include "GDEditLevelLayer.h"
#include "GDPauseLayer.h"
#include "GDPlayLayer.h"
#include "GDLevelCompleteLayer.h"
#include "GDOptionsLayer.h"

#include "SCToolsLayer.h"

auto cocos(const char* symbol) {
    static auto mod = GetModuleHandleA("libcocos2d.dll");
    return GetProcAddress(mod, symbol);
}

void CCKeyboardDispatcher_dispatchKeyboardMSG(CCKeyboardDispatcher* self, int key, bool down) {
    if (down && !GameManager::sharedState()->getGameVariable("6007")) {
        if(auto play_layer = gd::GameManager::sharedState()->getPlayLayer()){
            if(!play_layer->m_hasCompletedLevel && !play_layer->m_bIsPaused) {
                if(play_layer->get()->m_level->m_eLevelType == 2){
                    if (key == 'A') {
                        SCToolsLayer::applyLevelSpeed(1);
                    } else if (key == 'S') {
                        SCToolsLayer::applyLevelSpeed(0.75);
                    } else if (key == 'D') {
                        SCToolsLayer::applyLevelSpeed(0.5);
                    } else if (key == 'F') {
                        SCToolsLayer::applyLevelSpeed(0.25);
                    }
                }
                if(key == 'R') {
                    reinterpret_cast<void(__thiscall*)(PlayLayer*)>(base + 0x20BF00)(play_layer);
                }
            }
        }
    }
    matdash::orig<&CCKeyboardDispatcher_dispatchKeyboardMSG>(self, key, down);
}


void Hooks::Load() {

    GDMenuLayer::Hook();
    GDPlayLayer::Hook();
    GDPauseLayer::Hook();
    GDLevelCompleteLayer::Hook();
    GDEditLevelLayer::Hook();
    GDOptionsLayer::Hook();

    // from https://github.com/matcool/ReplayBot
    matdash::add_hook<&CCKeyboardDispatcher_dispatchKeyboardMSG>(cocos("?dispatchKeyboardMSG@CCKeyboardDispatcher@cocos2d@@QAE_NW4enumKeyCodes@2@_N@Z"));

}