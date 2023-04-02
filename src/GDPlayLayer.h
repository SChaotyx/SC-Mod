#pragma once

#include "includes.h"

class GDPlayLayer : public PlayLayer
{
    public:
    static void Hook();
    bool onQuit();
    bool onLevelComplete();
    bool onReset();
    bool onResume();
};