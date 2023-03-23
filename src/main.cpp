#include "includes.h"
#include <matdash/boilerplate.hpp>

#include "PauseLayerHook.h"
#include "MoreOptionsLayerHook.h"
#include "EndLevelLayerHook.h"
#include "MenuLayerHook.h"
#include "EditLevelLayerHook.h"
#include "CreatorToolsLayer.h"

#include <matdash/console.hpp>

void PlayLayer_onQuit(PlayLayer* self) {
	if(PlayLayer::get()->m_level->m_eLevelType == 2 ) CreatorToolsLayer::resetOnQuit();
    matdash::orig<&PlayLayer_onQuit>(self);
}

void mod_main(HMODULE) {
    
    matdash::create_console();
    
    PauseLayerHook::LoadHooks();
    MoreOptionsLayerHook::LoadHooks();
    EndLevelLayerHook::LoadHooks();
    MenuLayerHook::LoadHooks();
    EditLevelLayerHook::LoadHooks();
    matdash::add_hook<&PlayLayer_onQuit>(gd::base + 0x20D810);

}