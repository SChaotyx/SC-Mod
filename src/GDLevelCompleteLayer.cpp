#include "GDLevelCompleteLayer.h"
#include "GDPauseLayer.h"

void GDLevelCompleteLayer::Hook() {
    matdash::add_hook<&Init>(gd::base + 0x94CB0); //94CB0
}

bool GDLevelCompleteLayer::Init() {
    if(!matdash::orig<&GDLevelCompleteLayer::Init>(this)) return false;

    CCDirector *dir = CCDirector::sharedDirector();
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto menu = CCMenu::create();
	menu->setPosition(0,0);

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

    std::cout << PlayLayer::get()->m_level->m_nLevelID << std::endl;

    return true;
}