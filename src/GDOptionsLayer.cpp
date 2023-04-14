#include "GDOptionsLayer.h"
#include "SCOptionsLayer.h"

void GDOptionsLayer::Hook()
{
    matdash::add_hook<&GDOptionsLayer::Init>(base + 0x1DD420);
}

bool GDOptionsLayer::Init()
{
    matdash::orig<&GDOptionsLayer::Init>(this);

	CCDirector *dir = CCDirector::sharedDirector();

	auto layer = this->m_pLayer;
	unsigned int nodeCount = layer->getChildrenCount();

	for (unsigned int i = 0; i < nodeCount; i++)
	{
		auto nodes = reinterpret_cast<CCNode*>(layer->getChildren()->objectAtIndex(i));
		if(auto menu = dynamic_cast<CCMenu*>(nodes))
		{
			if(menu->getChildrenCount() > 1)
			{
				auto sprite = CCSprite::create("SC_optionsBtn_001.png");
				auto optBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCOptionsLayer::openCallback));
				optBtn->setPosition(-140, -70);
				optBtn->setScale(0.8f);
				optBtn->m_fBaseScale = 0.8f;
				menu->addChild(optBtn);

				auto menuMusicToggle = CCMenuItemToggler::create(
					CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"),
					CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"),
					this,
					menu_selector(GDOptionsLayer::onMenuMusicToggle)
				);
				menuMusicToggle->toggle(bool(GameManager::sharedState()->getGameVariable("0122")));
				menuMusicToggle->setPosition(140, -75);
				menuMusicToggle->setScale(0.7f);
				menu->addChild(menuMusicToggle);
				
				auto label = CCLabelBMFont::create("Menu\nMusic", "bigFont.fnt", 90, kCCTextAlignmentCenter);
				label->setPosition(140, -75 + 30);
				label->setScale(0.4f);
				menu->addChild(label);
			}
		}
	}
    return true;
}

void GDOptionsLayer::onMenuMusicToggle(CCObject*) {
        if (GameManager::sharedState()->getGameVariable("0122")) {
            GameManager::sharedState()->setGameVariable("0122", false);
			if(!GameManager::sharedState()->getPlayLayer())
            	GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
        }
        else {
            GameManager::sharedState()->setGameVariable("0122", true);
			if(!GameManager::sharedState()->getPlayLayer())
            	GameSoundManager::sharedState()->stopBackgroundMusic();
        }
}