#include "GDLevelCompleteLayer.h"
#include "GDPauseLayer.h"

void GDLevelCompleteLayer::Hook() {
    matdash::add_hook<&Init>(gd::base + 0x94CB0); //94CB0
}

bool GDLevelCompleteLayer::Init() {
    matdash::orig<&GDLevelCompleteLayer::Init>(this);

    CCDirector *dir = CCDirector::sharedDirector();
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto layer = this->m_pLayer;
	unsigned int nodeCount = layer->getChildrenCount();

	for (unsigned int i = 0; i < nodeCount; i++) {
		auto nodes = reinterpret_cast<CCNode*>(layer->getChildren()->objectAtIndex(i));
		if(auto menu = dynamic_cast<CCMenu*>(nodes)) {
			if(menu->getChildrenCount() > 1) {
				
				if(PlayLayer::get()->m_level->m_nLevelID) {
					auto infoBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), this, (SEL_MenuHandler)(&GDPauseLayer::levelInfoLayer));
					infoBtn->setPosition(182.5, 40);
					infoBtn->setScale(0.85f);
					infoBtn->m_fBaseScale = 0.85f;
					menu->addChild(infoBtn);

					auto ldbrBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png"), this, (SEL_MenuHandler)(&GDPauseLayer::levelLeaderboardLayer));
					ldbrBtn->setPosition(182.5, -5);
					ldbrBtn->setScale(0.85f);
					ldbrBtn->m_fBaseScale = 0.85f;
					menu->addChild(ldbrBtn);

					if (PlayLayer::get()->m_level->m_eLevelType != 2 ) {
						auto challBtn = CCMenuItemSpriteExtra::create(CCSprite::create("SC_QuestBtn_001.png"), this, (SEL_MenuHandler)(&GDPauseLayer::challengesLayer));
						challBtn->setPosition(182.5, -50);
						challBtn->setScale(0.85f);
						challBtn->m_fBaseScale = 0.85f;
						menu->addChild(challBtn);
					}
				}

			}
		}
	}

    return true;
}