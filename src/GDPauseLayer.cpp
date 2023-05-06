#include "GDPauseLayer.h"
#include "SCToolsLayer.h"
#include "SCToolBox.h"
#include "SCReplayLayer.h"

void GDPauseLayer::Hook()
{
    matdash::add_hook<&GDPauseLayer::Init>(base + 0x1E4620);
    matdash::add_hook<&GDPauseLayer::onEditor>(base + 0x1E60E0);
    matdash::add_hook<&GDPauseLayer::onResume>(base + 0x1e5fa0);
}

bool GDPauseLayer::Init()
{
    matdash::orig<&GDPauseLayer::Init>(this);

	CCDirector *dir = CCDirector::sharedDirector();
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto menu = CCMenu::create();
	menu->setPosition(0,0);

	auto sprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
	auto optBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDPauseLayer::optionsLayer));
	optBtn->setPosition(50, winSize.height - 85);
	optBtn->setScale(0.80f);
	optBtn->m_fBaseScale = 0.80f;
	menu->addChild(optBtn);

	sprite = CCSprite::create("SC_ReplayBtn_001.png");
	auto replayBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCReplayLayer::openCallback));
	replayBtn->setPosition(50, winSize.height - 130);
	replayBtn->setScale(0.85f);
	replayBtn->m_fBaseScale = 0.85f;
	menu->addChild(replayBtn);
	
	if(PlayLayer::get()->m_level->m_nLevelID)
	{
		sprite = CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png");
		auto infoBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDPauseLayer::levelInfoLayer));
		infoBtn->setPosition(winSize.width - 50, winSize.height - 85);
		infoBtn->setScale(0.85f);
		infoBtn->m_fBaseScale = 0.85f;
		menu->addChild(infoBtn);

		sprite = CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png");
		auto ldbrBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDPauseLayer::levelLeaderboardLayer));
    	ldbrBtn->setPosition(winSize.width - 50, winSize.height - 130);
		ldbrBtn->setScale(0.85f);
		ldbrBtn->m_fBaseScale = 0.85f;
		menu->addChild(ldbrBtn);
	}

	if(PlayLayer::get()->m_level->m_eLevelType == kGJLevelTypeEditor )
	{
		sprite = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
		auto COptBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCToolsLayer::openCallback));
		COptBtn->setPosition(50, winSize.height - 175);
		COptBtn->setScale(0.85f);
		COptBtn->m_fBaseScale = 0.85f;
		menu->addChild(COptBtn);
	} else {
		sprite = CCSprite::create("SC_QuestBtn_001.png");
		auto challBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDPauseLayer::challengesLayer));
    	challBtn->setPosition(winSize.width - 50, winSize.height - 175);
		challBtn->setScale(0.85f);
		challBtn->m_fBaseScale = 0.85f;
		menu->addChild(challBtn);
	}

	this->addChild(menu);
    return true;
}

void GDPauseLayer::challengesLayer(CCObject* pSender)
{
	ChallengesPage::create()->show();
}

void GDPauseLayer::optionsLayer(CCObject* pSender)
{
	auto layer = OptionsLayer::create();
	CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 100);
	layer->showLayer(false);
}

FLAlertLayer* GDPauseLayer::CreateLevelInfoLayer(GJGameLevel* level)
{
	return reinterpret_cast<FLAlertLayer*(__fastcall*)
	(GJGameLevel*, GJUserScore*)>(base + 0x14F4F0)(level, nullptr);
}

void GDPauseLayer::levelInfoLayer(CCObject* pSender)
{
	GDPauseLayer::CreateLevelInfoLayer(PlayLayer::get()->m_level)->show();
}

FLAlertLayer* GDPauseLayer::CreateLevelLeaderboardLayer(GJGameLevel* level)
{
	return reinterpret_cast<FLAlertLayer*(__fastcall*)
	(GJGameLevel*, GJUserScore*)>(base + 0x17c440)(level, nullptr);
}

void GDPauseLayer::levelLeaderboardLayer(CCObject* pSender)
{
	GDPauseLayer::CreateLevelLeaderboardLayer(PlayLayer::get()->m_level)->show();
}

bool GDPauseLayer::onResume(PlayLayer* self)
{
    matdash::orig<&GDPauseLayer::onResume>(this, self);
	float levelSpeed = CCDirector::sharedDirector()->getScheduler()->getTimeScale();
	if(levelSpeed != 1)SCToolBox::setSongPitch(levelSpeed);
	return true;
}

bool GDPauseLayer::onEditor(PlayLayer* self)
{
	if(PlayLayer::get()->m_level->m_eLevelType == kGJLevelTypeEditor ) SCToolsLayer::resetOnQuit();
    matdash::orig<&GDPauseLayer::onEditor>(this, self);
	return true;
}
/*
void GDPauseLayer::Resume(CCObject* pSender)
{
	reinterpret_cast<void(__thiscall*)
	(PauseLayer*, cocos2d::CCObject*)>(base + 0x1e5fa0)(this, pSender);
}
*/
    