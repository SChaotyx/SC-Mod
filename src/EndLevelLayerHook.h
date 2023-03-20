#pragma once

#include "includes.h"

class EndLevelLayerHook : public PlayLayer {
    public:
    static void LoadHooks();
    bool EndLevelLayerHookInit();
};