#include "CreatorToolsLayer.h"
#include "MoreOptionsLayerHook.h"

bool noclipEnabled = false;

void CreatorToolsLayer::resetOnQuit(){ 
    std::cout << "Reset on Quit" << std::endl;
    if(noclipEnabled) noclipToggler();
    CreatorToolsLayer::applyLevelSpeed(1);
}

void CreatorToolsLayer::toggleNoclip(CCObject*) {
    noclipToggler();
}

void CreatorToolsLayer::noclipToggler() {
    noclipEnabled = !noclipEnabled;
    if(noclipEnabled) {
        MoreOptionsLayerHook::patchMemory(reinterpret_cast<void*>(base + 0x20A23C), {0xE9, 0x79, 0x06, 0x00, 0x00});
        std::cout << "noclip enabled" << std::endl;
    } else {
        MoreOptionsLayerHook::patchMemory(reinterpret_cast<void*>(base + 0x20A23C), {0x6A, 0x14, 0x8B, 0xCB, 0xFF});
        std::cout << "noclip disabled" << std::endl;
    }
}

auto CreatorToolsLayer::noclipTest(CCSprite* check_on_sprite, CCSprite* check_off_sprite){
    return (noclipEnabled) ? check_on_sprite : check_off_sprite;
}

auto CreatorToolsLayer::create() {
        auto node = new CreatorToolsLayer();
        if (node && node->init()) {
            node->autorelease();
        } else {
            CC_SAFE_DELETE(node);
        }
        return node;
}

void CreatorToolsLayer::openCallback(CCObject*) {

    auto node = create();
    auto dir = CCDirector::sharedDirector();
    auto scene = dir->getRunningScene();

    if(scene->getChildByTag(0xAE) == nullptr) {
        scene->addChild(node, 1000);

        node->registerWithTouchDispatcher();
        dir->getTouchDispatcher()->incrementForcePrio(2);
    }
}

bool CreatorToolsLayer::init() {

     if(!initWithColor(ccc4(0, 0, 0, 105))) return false;

    auto dir = CCDirector::sharedDirector();
    auto win_size = CCDirector::sharedDirector()->getWinSize();

    //setZOrder(20);
    setTag(0xAE);

    float menusizeX = 210;
    float menusizeY = 82;

    auto menu = CCMenu::create();
    menu->setPosition(50+12, 40+12);
    addChild(menu);

    this->registerWithTouchDispatcher();
    CCDirector::sharedDirector()->getTouchDispatcher()->incrementForcePrio(1);

    auto bg = extension::CCScale9Sprite::create("GJ_square02.png", {0, 0, 80, 80});
    bg->setContentSize(CCSize(menusizeX,menusizeY));
    bg->setPosition(menusizeX / 2, menusizeY / 2);

    menu->addChild(bg);

    auto sprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    sprite->setScale(0.75f);
    auto btn = gd::CCMenuItemSpriteExtra::create(sprite, this, menu_selector(CreatorToolsLayer::closeCallback));
    btn->setPosition(-12,-12);
    menu->addChild(btn);

    auto label = CCLabelBMFont::create("Noclip", "bigFont.fnt");
    label->setScale(0.4f);
    label->setPosition(60, 20);
    menu->addChild(label);

    CCMenuItemToggler* noclipBtn;
    auto* const check_off_sprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    auto* const check_on_sprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    noclipBtn = CCMenuItemToggler::create(noclipTest(check_on_sprite, check_off_sprite), noclipTest(check_off_sprite, check_on_sprite), this, menu_selector(CreatorToolsLayer::toggleNoclip));
    noclipBtn->setScale(0.5f);
    noclipBtn->setPosition(25, 20);
    menu->addChild(noclipBtn);

    sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    sprite->setScale(0.5f);
    label = CCLabelBMFont::create("x1", "bigFont.fnt");
    label->setScale(0.5f);
    label->setPosition(40,42);
    sprite->addChild(label);
    btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(CreatorToolsLayer::setLevelSpeed1));
    btn->setPosition(30, menusizeY - 30);
    menu->addChild(btn);

    sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    sprite->setScale(0.5f);
    label = CCLabelBMFont::create("x0.75", "bigFont.fnt");
    label->setScale(0.5f);
    label->setPosition(40,42);
    sprite->addChild(label);
    btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(CreatorToolsLayer::setLevelSpeed2));
    btn->setPosition(30 + 50, menusizeY - 30);
    menu->addChild(btn);

    sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    sprite->setScale(0.5f);
    label = CCLabelBMFont::create("x0.5", "bigFont.fnt");
    label->setScale(0.5f);
    label->setPosition(40,42);
    sprite->addChild(label);
    btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(CreatorToolsLayer::setLevelSpeed3));
    btn->setPosition(30 + 100, menusizeY - 30);
    menu->addChild(btn);

    sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    sprite->setScale(0.5f);
    label = CCLabelBMFont::create("x0.25", "bigFont.fnt");
    label->setScale(0.5f);
    label->setPosition(40,42);
    sprite->addChild(label);
    btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(CreatorToolsLayer::setLevelSpeed4));
    btn->setPosition(30 + 150, menusizeY - 30);
    menu->addChild(btn);


    setKeypadEnabled(true);
    setTouchEnabled(true);
    return true;
}

void CreatorToolsLayer::applyLevelSpeed(float levelSpeed) {
    auto dir = CCDirector::sharedDirector();
    dir->getScheduler()->setTimeScale(levelSpeed);
    std::cout << "set time scale to: " << levelSpeed << std::endl;
}

void CreatorToolsLayer::setLevelSpeed1(CCObject*) { CreatorToolsLayer::applyLevelSpeed(1); CreatorToolsLayer::keyBackClicked(); }
void CreatorToolsLayer::setLevelSpeed2(CCObject*) { CreatorToolsLayer::applyLevelSpeed(0.75); CreatorToolsLayer::keyBackClicked(); }
void CreatorToolsLayer::setLevelSpeed3(CCObject*) { CreatorToolsLayer::applyLevelSpeed(0.5); CreatorToolsLayer::keyBackClicked(); }
void CreatorToolsLayer::setLevelSpeed4(CCObject*) { CreatorToolsLayer::applyLevelSpeed(0.25); CreatorToolsLayer::keyBackClicked(); }

void CreatorToolsLayer::keyBackClicked() {
    gd::FLAlertLayer::keyBackClicked();
}