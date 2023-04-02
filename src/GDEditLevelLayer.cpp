#include "GDEditLevelLayer.h"

void GDEditLevelLayer::Hook()
{
    matdash::add_hook<&GDEditLevelLayer::Init>(base + 0x6f5d0);
}

bool GDEditLevelLayer::Init(GJGameLevel* level)
{
    matdash::orig<&GDEditLevelLayer::Init>(this, level);

	CCDirector *dir = CCDirector::sharedDirector();
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto menu = CCMenu::create();
	menu->setPosition(0,0);
	this->addChild(menu);

    if(m_pLevel->m_nLevelID)
    {
        auto sprite = CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png");
        auto infoBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDEditLevelLayer::levelInfoLayer));
        infoBtn->setPosition((winSize.width / 2) + 165, (winSize.height / 2) - 10);
        infoBtn->setScale(0.6f);
        infoBtn->m_fBaseScale = 0.6f;
        menu->addChild(infoBtn);

        sprite = CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png");
        auto ldbrBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDEditLevelLayer::levelLeaderboardLayer));
        ldbrBtn->setPosition((winSize.width / 2) + 165, (winSize.height / 2) - 40);
        ldbrBtn->setScale(0.6f);
        ldbrBtn->m_fBaseScale = 0.6f;
        menu->addChild(ldbrBtn);
    }
	return true;
}

FLAlertLayer* GDEditLevelLayer::CreateLevelInfoLayer(GJGameLevel* level)
{
	return reinterpret_cast<FLAlertLayer*(__fastcall*)
    (GJGameLevel*, GJUserScore*)>(base + 0x14F4F0)(level, nullptr);
}

void GDEditLevelLayer::levelInfoLayer(cocos2d::CCObject* pSender)
{
	GDEditLevelLayer::CreateLevelInfoLayer(m_pLevel)->show();
}

FLAlertLayer* GDEditLevelLayer::CreateLevelLeaderboardLayer(GJGameLevel* level)
{
	return reinterpret_cast<FLAlertLayer*(__fastcall*)
    (GJGameLevel*, GJUserScore*)>(base + 0x17c440)(level, nullptr);
}

void GDEditLevelLayer::levelLeaderboardLayer(cocos2d::CCObject* pSender)
{
	GDEditLevelLayer::CreateLevelLeaderboardLayer(m_pLevel)->show();
}