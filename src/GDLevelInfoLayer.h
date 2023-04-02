#pragma once

#include "includes.h"

class GDLevelInfoLayer : public LevelInfoLayer
{
    public:
    static void Hook();
    bool Init(GJGameLevel*);
    void toOptions(CCObject*);
};