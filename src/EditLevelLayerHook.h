#pragma once

#include "includes.h"

class EditLevelLayerHook : public EditLevelLayer {
	public:
    static void LoadHooks();
	bool EditLevelLayerInit(GJGameLevel*);

    static FLAlertLayer* CreateLevelInfoLayer(GJGameLevel* level);
	void levelInfoLayer(cocos2d::CCObject* pSender);

    static FLAlertLayer* CreateLevelLeaderboardLayer(GJGameLevel* level);
	void levelLeaderboardLayer(cocos2d::CCObject* pSender);
};