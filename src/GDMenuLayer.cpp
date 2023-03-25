#include "GDMenuLayer.h"
#include "SCManager.h"

void GDMenuLayer::Hook() {
    matdash::add_hook<&GDMenuLayer::Init>(base + 0x1907B0);
}

bool GDMenuLayer::Init() {
    if(!matdash::orig<&GDMenuLayer::Init>(this)) return false;
    GDMenuLayer::AccountIcon();
	SCManager::StartUpCheck();
	return true;
}

//From https://github.com/MikaKC/FutureDash
void GDMenuLayer::AccountIcon() {

    int count = this->getChildrenCount();

	auto node = (CCNode*)this->getChildren()->objectAtIndex(2);
	auto menu = dynamic_cast<CCMenu*>(node);
    auto button = (CCMenuItemSpriteExtra*)menu->getChildren()->objectAtIndex(3);
	auto spr = (CCSprite*)button->getChildren()->objectAtIndex(0);

    auto bluebtn = CCSprite::create("SC_ProfileBtn_001.png");
    spr->addChild(bluebtn);
	spr->setDisplayFrame(bluebtn->displayFrame());

    AccIconBtn = SimplePlayer::create(0);
    AccIconBtn->updatePlayerFrame(frameIcon(GameManager::sharedState()->getPlayerIconType()), GameManager::sharedState()->getPlayerIconType());
	AccIconBtn->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));
	AccIconBtn->setSecondColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
	AccIconBtn->setGlowOutline(GameManager::sharedState()->getPlayerGlow());
    AccIconBtn->setScale(0.90f);
    AccIconBtn->setPositionX(-0.55f);
    AccIconBtn->setPositionY(+1.35f);
	spr->addChild(AccIconBtn);
	spr->setDisplayFrame(AccIconBtn->displayFrame());

	return;
}

int GDMenuLayer::frameIcon(IconType icon) {
	switch(icon) {
		default: return GameManager::sharedState()->getPlayerFrame();
		case IconType::kIconTypeShip: return GameManager::sharedState()->getPlayerShip();
		case IconType::kIconTypeBall: return GameManager::sharedState()->getPlayerBall();
		case IconType::kIconTypeUfo: return GameManager::sharedState()->getPlayerBird();
		case IconType::kIconTypeWave: return GameManager::sharedState()->getPlayerDart();
		case IconType::kIconTypeRobot: return GameManager::sharedState()->getPlayerRobot();
		case IconType::kIconTypeSpider: return GameManager::sharedState()->getPlayerSpider();
	}
}