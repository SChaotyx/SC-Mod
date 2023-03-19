#include "PauseLayerHook.h"
#include "MoreOptionsLayerHook.h"

void PauseLayerHook::LoadHooks() {
    matdash::add_hook<&PauseLayerHook::PauseLayerInit>(base + 0x1E4620);
}

bool PauseLayerHook::PauseLayerInit() {

    if(!matdash::orig<&PauseLayerHook::PauseLayerInit>(this)) return false;
	MoreOptionsLayerHook::OptionCheckUpdate();

	CCDirector *dir = CCDirector::sharedDirector();
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto optBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::optionsLayer));
	optBtn->setScale(0.85f);
	optBtn->setPosition(winSize.width - 50, 50);

    auto infoBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::levelInfoLayer));
	infoBtn->setScale(0.85f);
    infoBtn->setPosition(winSize.width - 50, winSize.height - 50);

	auto challBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::challengesLayer));
	challBtn->setScale(0.85f);
    challBtn->setPosition(winSize.width - 50, winSize.height - 160);

	auto ldbrBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::levelLeaderboardLayer));
	ldbrBtn->setScale(0.85f);
    ldbrBtn->setPosition(winSize.width - 50, winSize.height - 105);

	auto menu = CCMenu::create();
	menu->setPosition(0,0);
	menu->addChild(optBtn);
	menu->addChild(infoBtn);
	menu->addChild(challBtn);
	menu->addChild(ldbrBtn);
	this->addChild(menu);

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
    