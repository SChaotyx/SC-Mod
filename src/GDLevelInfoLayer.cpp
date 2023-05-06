#include "GDLevelInfoLayer.h"
#include "SCReplayLayer.h"

void GDLevelInfoLayer::Hook()
{
    matdash::add_hook<&GDLevelInfoLayer::Init>(base + 0x175df0);
}

bool GDLevelInfoLayer::Init(GJGameLevel* level)
{
    matdash::orig<&GDLevelInfoLayer::Init>(this, level);

    auto dir = CCDirector::sharedDirector();
    auto winSize = dir->getWinSize();
    
    auto menu = CCMenu::create();
    menu->setPosition(0,0);
    this->addChild(menu);

    auto sprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
    auto button = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDLevelInfoLayer::toOptions));
    button->setScale(0.8f);
    button->m_fBaseScale = 0.8f;
    button->setPosition(70, winSize.height - 23);
    menu->addChild(button);

    sprite = CCSprite::create("SC_ReplayBtn_001.png");
    auto replayBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCReplayLayer::openCallback));
	replayBtn->setScale(0.85f);
	replayBtn->m_fBaseScale = 0.85f;
	replayBtn->setPosition(120, winSize.height - 23);
	menu->addChild(replayBtn);

    return true;
}

void GDLevelInfoLayer::toOptions(CCObject* pSender)
{
    auto layer = OptionsLayer::create();
	cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 100);
	layer->showLayer(false);
}