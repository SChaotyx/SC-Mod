#include "GDEndLevelLayer.h"
#include "GDPauseLayer.h"

void GDEndLevelLayer::Hook()
{
    matdash::add_hook<&Init>(base + 0x94CB0); //94CB0
}

bool GDEndLevelLayer::Init()
{
    matdash::orig<&GDEndLevelLayer::Init>(this);

    CCDirector *dir = CCDirector::sharedDirector();
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto layer = this->m_pLayer;
	unsigned int nodeCount = layer->getChildrenCount();

	for (unsigned int i = 0; i < nodeCount; i++)
	{
		auto nodes = reinterpret_cast<CCNode*>(layer->getChildren()->objectAtIndex(i));
		if(auto menu = dynamic_cast<CCMenu*>(nodes))
		{
			if(menu->getChildrenCount() > 1)
			{
				if(PlayLayer::get()->m_level->m_nLevelID)
				{
					auto sprite = CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png");
					auto infoBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDPauseLayer::levelInfoLayer));
					infoBtn->setPosition(215, 40);
					infoBtn->setScale(0.85f);
					infoBtn->m_fBaseScale = 0.85f;
					menu->addChild(infoBtn);

					sprite = CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png");
					auto ldbrBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDPauseLayer::levelLeaderboardLayer));
					ldbrBtn->setPosition(215, -5);
					ldbrBtn->setScale(0.85f);
					ldbrBtn->m_fBaseScale = 0.85f;
					menu->addChild(ldbrBtn);

					if (!PlayLayer::get()->m_level->m_eLevelType == kGJLevelTypeEditor )
					{
						sprite =CCSprite::create("SC_QuestBtn_001.png");
						auto challBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GDPauseLayer::challengesLayer));
						challBtn->setPosition(215, -50);
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