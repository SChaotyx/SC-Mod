#pragma once

#include "includes.h"

class PauseLayerHook : public PauseLayer {
public:
    static void LoadHooks();
	bool PauseLayerInit();
	void practiceMusicBtn(CCObject*);
	auto PracticeMusicBtnToggle(CCSprite* toggleOn, CCSprite* toggleOff);
    static FLAlertLayer* CreateLevelInfoLayer(GJGameLevel* level);
	void levelInfoLayer(cocos2d::CCObject* pSender);
	void optionsLayer(cocos2d::CCObject* pSender);
	void extraOptLayer(cocos2d::CCObject* pSender);
};