#include "GDPauseLayer.h"
#include "SCToolsLayer.h"
#include "SCToolBox.h"

void GDPauseLayer::Hook() {
    matdash::add_hook<&GDPauseLayer::Init>(base + 0x1E4620);
    matdash::add_hook<&GDPauseLayer::onEditor>(base + 0x1E60E0);
    matdash::add_hook<&GDPauseLayer::onResume>(base + 0x1e5fa0);
}

bool GDPauseLayer::Init() {
    matdash::orig<&GDPauseLayer::Init>(this);

	CCDirector *dir = CCDirector::sharedDirector();
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto menu = CCMenu::create();
	menu->setPosition(0,0);

	auto optBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), this, (SEL_MenuHandler)(&GDPauseLayer::optionsLayer));
	optBtn->setPosition(winSize.width - 50, 40);
	optBtn->setScale(0.80f);
	optBtn->m_fBaseScale = 0.80f;
	menu->addChild(optBtn);

	if(PlayLayer::get()->m_level->m_eLevelType == 2 ){
		auto COptBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png"), this, (SEL_MenuHandler)(&SCToolsLayer::openCallback));
		COptBtn->setPosition(50, 40);
		COptBtn->setScale(0.85f);
		COptBtn->m_fBaseScale = 0.85f;
		menu->addChild(COptBtn);
	}
	
	if(PlayLayer::get()->m_level->m_nLevelID) {

		auto infoBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), this, (SEL_MenuHandler)(&GDPauseLayer::levelInfoLayer));
		infoBtn->setPosition(winSize.width - 50, winSize.height - 85);
		infoBtn->setScale(0.85f);
		infoBtn->m_fBaseScale = 0.85f;
		menu->addChild(infoBtn);

		auto ldbrBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png"), this, (SEL_MenuHandler)(&GDPauseLayer::levelLeaderboardLayer));
    	ldbrBtn->setPosition(winSize.width - 50, winSize.height - 130);
		ldbrBtn->setScale(0.85f);
		ldbrBtn->m_fBaseScale = 0.85f;
		menu->addChild(ldbrBtn);

		if (PlayLayer::get()->m_level->m_eLevelType != 2 ) {
			auto challBtn = CCMenuItemSpriteExtra::create(CCSprite::create("SC_QuestBtn_001.png"), this, (SEL_MenuHandler)(&GDPauseLayer::challengesLayer));
    		challBtn->setPosition(winSize.width - 50, winSize.height - 175);
			challBtn->setScale(0.85f);
			challBtn->m_fBaseScale = 0.85f;
			menu->addChild(challBtn);
		}

	}

	this->addChild(menu);

    return true;
}

void GDPauseLayer::challengesLayer(cocos2d::CCObject* pSender){
	ChallengesPage::create()->show();
}

void GDPauseLayer::optionsLayer(cocos2d::CCObject* pSender) {
	//MoreOptionsLayer::create()->show();
	auto layer = OptionsLayer::create();
	cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 100);
	layer->showLayer(false);
}

FLAlertLayer* GDPauseLayer::CreateLevelInfoLayer(GJGameLevel* level) {
	return reinterpret_cast<FLAlertLayer*(__fastcall*)(GJGameLevel*, GJUserScore*)>(
		base + 0x14F4F0
	)(level, nullptr);
}

void GDPauseLayer::levelInfoLayer(cocos2d::CCObject* pSender) {
	GDPauseLayer::CreateLevelInfoLayer(PlayLayer::get()->m_level)->show();
}

FLAlertLayer* GDPauseLayer::CreateLevelLeaderboardLayer(GJGameLevel* level) {
	return reinterpret_cast<FLAlertLayer*(__fastcall*)(GJGameLevel*, GJUserScore*)>(
		base + 0x17c440
	)(level, nullptr);
}

void GDPauseLayer::levelLeaderboardLayer(cocos2d::CCObject* pSender) {
	GDPauseLayer::CreateLevelLeaderboardLayer(PlayLayer::get()->m_level)->show();
}

bool GDPauseLayer::onResume(PlayLayer* self) {
    matdash::orig<&GDPauseLayer::onResume>(this, self);
	float levelSpeed = CCDirector::sharedDirector()->getScheduler()->getTimeScale();
	if(levelSpeed != 1)SCToolBox::setSongPitch(levelSpeed);
	return true;
}

bool GDPauseLayer::onEditor(PlayLayer* self) {
	if(PlayLayer::get()->m_level->m_eLevelType == 2 ) SCToolsLayer::resetOnQuit();
    matdash::orig<&GDPauseLayer::onEditor>(this, self);
	return true;
}
/*
void GDPauseLayer::Resume(CCObject* pSender) {
	reinterpret_cast<void(__thiscall*)(PauseLayer*, cocos2d::CCObject*)>(
        base + 0x1e5fa0
    )(this, pSender);
}
*/
    