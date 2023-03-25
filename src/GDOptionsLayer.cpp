#include "GDOptionsLayer.h"
#include "SCOptionsLayer.h"

void GDOptionsLayer::Hook() {
    matdash::add_hook<&GDOptionsLayer::Init>(base + 0x1DD420);
}

bool GDOptionsLayer::Init() {
    if(!matdash::orig<&GDOptionsLayer::Init>(this)) return false;
	CCDirector *dir = CCDirector::sharedDirector();
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto menu = CCMenu::create();
	menu->setPosition(0,0);

	auto optBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), this, (SEL_MenuHandler)(&SCOptionsLayer::openCallback));
	optBtn->setPosition(winSize.width -40 , 40);
	optBtn->setScale(0.80f);
	optBtn->m_fBaseScale = 0.80f;
	menu->addChild(optBtn);

    this->addChild(menu);
    return true;
}