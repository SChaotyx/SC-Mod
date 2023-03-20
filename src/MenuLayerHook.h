#pragma once

#include "includes.h"

class MenuLayerHook : public MenuLayer {
    public:
    SimplePlayer* AccIconBtn;

    public:
    static void LoadHooks();
    bool MenuLayerHookInit();
    void AccountIcon();
    int frameIcon(IconType icon);
};