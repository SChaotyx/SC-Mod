#include "includes.h"
#include <matdash/boilerplate.hpp>

#include "PauseLayerHook.h"
#include "MoreOptionsLayerHook.h"
#include "EndLevelLayerHook.h"
#include "MenuLayerHook.h"
#include "EditLevelLayerHook.h"

#include <matdash/console.hpp>

void mod_main(HMODULE) {
    
    matdash::create_console();
    
    PauseLayerHook::LoadHooks();
    MoreOptionsLayerHook::LoadHooks();
    EndLevelLayerHook::LoadHooks();
    MenuLayerHook::LoadHooks();
    EditLevelLayerHook::LoadHooks();

}