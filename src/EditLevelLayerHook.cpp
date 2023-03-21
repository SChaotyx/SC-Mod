#include "EditLevelLayerHook.h"

void EditLevelLayerHook::LoadHooks() {
    matdash::add_hook<&EditLevelLayerHook::EditLevelLayerInit>(base + 0x6f5d0);
}

bool EditLevelLayerHook::EditLevelLayerInit(GJGameLevel* level) {
    if(!matdash::orig<&EditLevelLayerHook::EditLevelLayerInit>(this, level)) return false;

	CCDirector *dir = CCDirector::sharedDirector();
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto menu = CCMenu::create();
	menu->setPosition(0,0);

    if(m_pLevel->m_nLevelID){
        auto infoBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), this, (SEL_MenuHandler)(&EditLevelLayerHook::levelInfoLayer));
        infoBtn->setPosition(winSize.width - 120, winSize.height - 170);
        infoBtn->setScale(0.6f);
        infoBtn->m_fBaseScale = 0.6f;
        menu->addChild(infoBtn);

        auto ldbrBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png"), this, (SEL_MenuHandler)(&EditLevelLayerHook::levelLeaderboardLayer));
        ldbrBtn->setPosition(winSize.width - 120, winSize.height - 200);
        ldbrBtn->setScale(0.6f);
        ldbrBtn->m_fBaseScale = 0.6f;
        menu->addChild(ldbrBtn);
    }

	this->addChild(menu);

	return true;
}

FLAlertLayer* EditLevelLayerHook::CreateLevelInfoLayer(GJGameLevel* level) {
	return reinterpret_cast<FLAlertLayer*(__fastcall*)(GJGameLevel*, GJUserScore*)>(
		base + 0x14F4F0
	)(level, nullptr);
}

void EditLevelLayerHook::levelInfoLayer(cocos2d::CCObject* pSender) {
	EditLevelLayerHook::CreateLevelInfoLayer(m_pLevel)->show();
}

FLAlertLayer* EditLevelLayerHook::CreateLevelLeaderboardLayer(GJGameLevel* level) {
	return reinterpret_cast<FLAlertLayer*(__fastcall*)(GJGameLevel*, GJUserScore*)>(
		base + 0x17c440
	)(level, nullptr);
}

void EditLevelLayerHook::levelLeaderboardLayer(cocos2d::CCObject* pSender) {
	EditLevelLayerHook::CreateLevelLeaderboardLayer(m_pLevel)->show();
}