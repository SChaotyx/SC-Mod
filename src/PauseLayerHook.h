#pragma once

#include "includes.h"

class PauseLayerHook : public PauseLayer {
public:
    static void LoadHooks();
	bool PauseLayerInit();

    static FLAlertLayer* CreateLevelInfoLayer(GJGameLevel* level);
	void levelInfoLayer(cocos2d::CCObject* pSender);

    static FLAlertLayer* CreateLevelLeaderboardLayer(GJGameLevel* level);
	void levelLeaderboardLayer(cocos2d::CCObject* pSender);

	void optionsLayer(cocos2d::CCObject* pSender);

	void challengesLayer(cocos2d::CCObject* pSender);

	void extraOptLayer(cocos2d::CCObject* pSender);

	void CreatorOpt(cocos2d::CCObject* pSender);
};