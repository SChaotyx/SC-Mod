#pragma once

#include "includes.h"

class GDPlayLayer : public PlayLayer
{
    public:
    static void Hook();
    bool Init(GJGameLevel*);
    void Update(float);
    void updateVisibility();

    void onLevelComplete();
    void onPauseGame(bool);
    void onReset();
    void onQuit();

    static void onPushButton(PlayLayer*, int, bool);
    static void onReleaseButton(PlayLayer*, int, bool);
    CCObject* createCheckpoint();
};