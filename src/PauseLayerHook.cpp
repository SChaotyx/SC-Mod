#include "PauseLayerHook.h"
#include "MoreOptionsLayerHook.h"

void PauseLayerHook::LoadHooks() {
    matdash::add_hook<&PauseLayerHook::PauseLayerInit>(base + 0x1E4620);
}

bool PauseLayerHook::PauseLayerInit() {

    if(!matdash::orig<&PauseLayerHook::PauseLayerInit>(this)) return false;

	CCDirector *dir = CCDirector::sharedDirector();
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto menu = CCMenu::create();
	menu->setPosition(0,0);

	auto optBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::optionsLayer));
	optBtn->setPosition(winSize.width - 50, 40);
	optBtn->setScale(0.80f);
	optBtn->m_fBaseScale = 0.80f;
	menu->addChild(optBtn);

	if(PlayLayer::get()->m_level->m_nLevelID) {

		auto infoBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::levelInfoLayer));
		infoBtn->setPosition(winSize.width - 50, winSize.height - 85);
		infoBtn->setScale(0.85f);
		infoBtn->m_fBaseScale = 0.85f;
		menu->addChild(infoBtn);

		auto ldbrBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::levelLeaderboardLayer));
    	ldbrBtn->setPosition(winSize.width - 50, winSize.height - 130);
		ldbrBtn->setScale(0.85f);
		ldbrBtn->m_fBaseScale = 0.85f;
		menu->addChild(ldbrBtn);

		if (PlayLayer::get()->m_level->m_eLevelType != 2 ) {
			auto challBtn = CCMenuItemSpriteExtra::create(CCSprite::create("SC_QuestBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::challengesLayer));
    		challBtn->setPosition(winSize.width - 50, winSize.height - 175);
			challBtn->setScale(0.85f);
			challBtn->m_fBaseScale = 0.85f;
			menu->addChild(challBtn);
		}

	}

	this->addChild(menu);

	if(!GameManager::sharedState()->getGameVariable("6006")) MoreOptionsLayerHook::OptionCheckUpdate();

    return true;
}

void PauseLayerHook::challengesLayer(cocos2d::CCObject* pSender){
	ChallengesPage::create()->show();
}

void PauseLayerHook::optionsLayer(cocos2d::CCObject* pSender) {
	//MoreOptionsLayer::create()->show();
	auto layer = OptionsLayer::create();
	cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 100);
	layer->showLayer(false);
}

FLAlertLayer* PauseLayerHook::CreateLevelInfoLayer(GJGameLevel* level) {
	return reinterpret_cast<FLAlertLayer*(__fastcall*)(GJGameLevel*, GJUserScore*)>(
		base + 0x14F4F0
	)(level, nullptr);
}

void PauseLayerHook::levelInfoLayer(cocos2d::CCObject* pSender) {
	PauseLayerHook::CreateLevelInfoLayer(PlayLayer::get()->m_level)->show();
}

FLAlertLayer* PauseLayerHook::CreateLevelLeaderboardLayer(GJGameLevel* level) {
	return reinterpret_cast<FLAlertLayer*(__fastcall*)(GJGameLevel*, GJUserScore*)>(
		base + 0x17c440
	)(level, nullptr);
}

void PauseLayerHook::levelLeaderboardLayer(cocos2d::CCObject* pSender) {
	PauseLayerHook::CreateLevelLeaderboardLayer(PlayLayer::get()->m_level)->show();
}
    