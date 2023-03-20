#include "includes.h"
#include <matdash/boilerplate.hpp>
#include "PauseLayerHook.h"
#include "MoreOptionsLayerHook.h"
#include "EndLevelLayerHook.h"
#include "MenuLayerHook.h"

void mod_main(HMODULE) {

    PauseLayerHook::LoadHooks();
    MoreOptionsLayerHook::LoadHooks();
    EndLevelLayerHook::LoadHooks();
    MenuLayerHook::LoadHooks();

}