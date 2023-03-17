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
	optBtn->setPosition(winSize.width - 50, winSize.height - 50);

    auto infoBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), this, (SEL_MenuHandler)(&PauseLayerHook::levelInfoLayer));
	infoBtn->setScale(0.85f);
    infoBtn->setPosition(winSize.width - 50, winSize.height - 105);

	auto menu = CCMenu::create();
	menu->setPosition(0,0);
	menu->addChild(optBtn);
	menu->addChild(infoBtn);
	this->addChild(menu);

    return true;
}

void PauseLayerHook::optionsLayer(cocos2d::CCObject* pSender) {
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
    