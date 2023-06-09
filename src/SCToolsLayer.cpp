#include "SCToolsLayer.h"
#include "SCToolBox.h"


bool noclipEnabled = false;
auto SCToolsLayer::noclipCheck(CCSprite* check_on_sprite, CCSprite* check_off_sprite){
    return (noclipEnabled) ? check_on_sprite : check_off_sprite;
}

bool SCToolsLayer::init() {
    if(!initWithColor(ccc4(0, 0, 0, 130))) return false;

    auto dir = CCDirector::sharedDirector();
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    float menusizeX = 210, menusizeY = 82;
    float menuposX = 62, menuposY = 52;

    m_pButtonMenu = CCMenu::create();
    m_pButtonMenu->setPosition(menuposX, menuposY);
    addChild(m_pButtonMenu);

    auto bg = extension::CCScale9Sprite::create("GJ_square02.png", {0, 0, 80, 80});
    bg->setContentSize(CCSize(menusizeX,menusizeY));
    bg->setPosition(menusizeX / 2, menusizeY / 2);
    m_pButtonMenu->addChild(bg);

    auto sprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    sprite->setScale(0.75f);
    auto btn = gd::CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCToolsLayer::closeCallback));
    btn->setPosition(-12,-12);
    m_pButtonMenu->addChild(btn);

    sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    sprite->setScale(0.5f);
    auto label = CCLabelBMFont::create("x1", "bigFont.fnt");
    label->setScale(0.5f);
    label->setPosition(40,42);
    sprite->addChild(label);
    btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCToolsLayer::setLevelSpeed));
    btn->setTag(1);
    btn->setPosition(30, menusizeY - 30);
    m_pButtonMenu->addChild(btn);

    sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    sprite->setScale(0.5f);
    label = CCLabelBMFont::create("x0.75", "bigFont.fnt");
    label->setScale(0.5f);
    label->setPosition(40,42);
    sprite->addChild(label);
    btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCToolsLayer::setLevelSpeed));
    btn->setTag(2);
    btn->setPosition(30 + 50, menusizeY - 30);
    m_pButtonMenu->addChild(btn);

    sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    sprite->setScale(0.5f);
    label = CCLabelBMFont::create("x0.5", "bigFont.fnt");
    label->setScale(0.5f);
    label->setPosition(40,42);
    sprite->addChild(label);
    btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCToolsLayer::setLevelSpeed));
    btn->setTag(3);
    btn->setPosition(30 + 100, menusizeY - 30);
    m_pButtonMenu->addChild(btn);

    sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    sprite->setScale(0.5f);
    label = CCLabelBMFont::create("x0.25", "bigFont.fnt");
    label->setScale(0.5f);
    label->setPosition(40,42);
    sprite->addChild(label);
    btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCToolsLayer::setLevelSpeed));
    btn->setTag(4);
    btn->setPosition(30 + 150, menusizeY - 30);
    m_pButtonMenu->addChild(btn);

    label = CCLabelBMFont::create("Noclip", "bigFont.fnt");
    label->setScale(0.4f);
    label->setPosition(60, 20);
    m_pButtonMenu->addChild(label);

    CCMenuItemToggler* noclipBtn;
    auto* const check_off_sprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    auto* const check_on_sprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    noclipBtn = CCMenuItemToggler::create(noclipCheck(check_on_sprite, check_off_sprite), noclipCheck(check_off_sprite, check_on_sprite), this, menu_selector(SCToolsLayer::toggleNoclip));
    noclipBtn->setScale(0.5f);
    noclipBtn->setPosition(25, 20);
    m_pButtonMenu->addChild(noclipBtn);

    setTouchEnabled(true);
    setKeypadEnabled(true);

    return true;
}

void SCToolsLayer::openCallback(CCObject*)
{
    auto menu = create();
    auto dir = CCDirector::sharedDirector();
    auto scene = dir->getRunningScene();
    scene->addChild(menu, 1000);
    menu->registerWithTouchDispatcher();
    dir->getTouchDispatcher()->incrementForcePrio(2);
}

void SCToolsLayer::setLevelSpeed(CCObject* pSender)
{
    float lvlSpeed;
    switch(pSender->getTag())
    {
        case 1: lvlSpeed = 1; break;
        case 2: lvlSpeed = 0.75; break;
        case 3: lvlSpeed = 0.5; break;
        case 4: lvlSpeed = 0.25; break;
        default: lvlSpeed = 1; break;
    }
    SCToolBox::setLevelSpeed(lvlSpeed);
    SCToolsLayer::keyBackClicked();
}

void SCToolsLayer::decLevelSpeed(bool dec)
{
    float actualSpeed = CCDirector::sharedDirector()->getScheduler()->getTimeScale();
    float v = 0.25f;
    if(dec) {
        if(actualSpeed > 0.25) SCToolBox::setLevelSpeed(actualSpeed - v);
    } else {
        if(actualSpeed < 1.5) SCToolBox::setLevelSpeed(actualSpeed + v);
    }
}

void SCToolsLayer::keyBackClicked()
{
    FLAlertLayer::keyBackClicked();
}

void SCToolsLayer::toggleNoclip(CCObject*) { noclipToggler(); }

void SCToolsLayer::noclipToggler()
{
    noclipEnabled = !noclipEnabled;
    if(noclipEnabled) {
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20A23C), {0xE9, 0x79, 0x06, 0x00, 0x00});
        std::cout << "noclip enabled" << std::endl;
    } else {
        SCToolBox::patchMemory(reinterpret_cast<void*>(base + 0x20A23C), {0x6A, 0x14, 0x8B, 0xCB, 0xFF});
        std::cout << "noclip disabled" << std::endl;
    }
}

void SCToolsLayer::resetOnQuit()
{ 
    if(noclipEnabled) noclipToggler();
    if(CCDirector::sharedDirector()->getScheduler()->getTimeScale() != 1) SCToolBox::setLevelSpeed(1);
}