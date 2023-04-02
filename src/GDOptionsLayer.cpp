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
				auto sprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
				auto optBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCOptionsLayer::openCallback));
				optBtn->setPosition(150, -85);
				optBtn->setScale(0.8f);
				optBtn->m_fBaseScale = 0.8f;
				menu->addChild(optBtn);
			}
		}
	}
    return true;
}