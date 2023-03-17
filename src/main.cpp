#include "includes.h"
#include <matdash/boilerplate.hpp>
#include "PauseLayerHook.h"
#include "MoreOptionsLayerHook.h"

void mod_main(HMODULE) {
    PauseLayerHook::LoadHooks();
    MoreOptionsLayerHook::LoadHooks();
    MoreOptionsLayerHook::OptionCheckUpdate();
}