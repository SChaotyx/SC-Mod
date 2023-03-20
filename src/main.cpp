#include "includes.h"
#include <matdash/boilerplate.hpp>
#include "PauseLayerHook.h"
#include "MoreOptionsLayerHook.h"
#include "EndLevelLayerHook.h"

bool MenuLayer_init(MenuLayer* self) {
    if (!matdash::orig<&MenuLayer_init>(self)) return false;
    MoreOptionsLayerHook::OptionCheckUpdate();
    return true;
}

void mod_main(HMODULE) {

    matdash::add_hook<&MenuLayer_init>(gd::base + 0x1907B0);
    PauseLayerHook::LoadHooks();
    MoreOptionsLayerHook::LoadHooks();
    EndLevelLayerHook::LoadHooks();

}