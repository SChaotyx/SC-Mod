#include "SCReplayLayer.h"
#include "SCReplay.h"
#include <nfd.h>

bool SCReplayLayer::Init()
{
    if(!initWithColor(ccc4(0, 0, 0, 130))) return false;

    auto dir = CCDirector::sharedDirector();
    auto winSize = dir->getWinSize();

    m_pLayer = CCLayer::create();
    addChild(m_pLayer);

    m_pButtonMenu = CCMenu::create();
    m_pButtonMenu->setPosition(winSize.width / 2, winSize.height / 2);
    m_pLayer->addChild(m_pButtonMenu, 10);

    auto bg = extension::CCScale9Sprite::create("GJ_square04.png", {0, 0, 80, 80});
    bg->setContentSize(CCSize(400,280));
    m_pButtonMenu->addChild(bg);

    auto sprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    auto btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCReplayLayer::closeCallback));
    btn->setPosition(-195,135);
    m_pButtonMenu->addChild(btn);

    auto label = CCLabelBMFont::create("Replay", "bigFont.fnt");
    label->setScale(0.8f);
    label->setPosition(0, 125);
    m_pButtonMenu->addChild(label);

    auto btnsprite = extension::CCScale9Sprite::create("GJ_button_04.png", {0, 0, 40, 40});
    btnsprite->setContentSize(CCSize(55,25));

    btn = CCMenuItemSpriteExtra::create(btnsprite, this, menu_selector(SCReplayLayer::recordCallback));
    btn->setPosition(-105, 80);
    m_pButtonMenu->addChild(btn);
    label = CCLabelBMFont::create("Record", "goldFont.fnt");
    label->setScale(0.5f);
    label->setPosition(28, 14.5);
    label->setZOrder(1);
    btn->addChild(label);

    btn = CCMenuItemSpriteExtra::create(btnsprite, this, menu_selector(SCReplayLayer::playingCallback));
    btn->setPosition(-35, 80);
    m_pButtonMenu->addChild(btn);
    label = CCLabelBMFont::create("Play", "goldFont.fnt");
    label->setScale(0.6f);
    label->setPosition(28, 14.5);
    label->setZOrder(1);
    btn->addChild(label);

    btn = CCMenuItemSpriteExtra::create(btnsprite, this, menu_selector(SCReplayLayer::onSave));
    btn->setPosition(35,80);
    m_pButtonMenu->addChild(btn);
    label = CCLabelBMFont::create("Save", "goldFont.fnt");
    label->setScale(0.6f);
    label->setPosition(28, 14.5);
    label->setZOrder(1);
    btn->addChild(label);

    btn = CCMenuItemSpriteExtra::create(btnsprite, this, menu_selector(SCReplayLayer::onLoad));
    btn->setPosition(105,80);
    m_pButtonMenu->addChild(btn);
    label = CCLabelBMFont::create("Load", "goldFont.fnt");
    label->setScale(0.6f);
    label->setPosition(28, 14.5);
    label->setZOrder(1);
    btn->addChild(label);

    setTouchEnabled(true);
    setKeypadEnabled(true);

    return true;
}

void SCReplayLayer::openCallback(CCObject*)
{
    auto menu = create();
    auto dir = CCDirector::sharedDirector();
    auto scene = dir->getRunningScene();
    menu->show();
    menu->registerWithTouchDispatcher();
    dir->getTouchDispatcher()->incrementForcePrio(2);
}

void SCReplayLayer::keyBackClicked()
{
    FLAlertLayer::keyBackClicked();
}
void SCReplayLayer::recordCallback(CCObject*){ SCReplaySystem::get().setReplayMode(ReplayState::RECORDING); }
void SCReplayLayer::playingCallback(CCObject*){ SCReplaySystem::get().setReplayMode(ReplayState::PLAYING); }

void SCReplayLayer::onSave(CCObject*)
{
    nfdchar_t* path = nullptr;
    nfdfilteritem_t filterItem[1] = {{"SC-Mod Replay", "screp"}};
    auto result = NFD_SaveDialog(&path, filterItem, 1, NULL, NULL);
    if (result == NFD_OKAY) {
        SCReplaySystem::get().getReplay().save(path);
        FLAlertLayer::create(nullptr, "Info", "Ok", nullptr, "Replay saved.")->show();
        free(path);
    }
}

void SCReplayLayer::onLoad(CCObject*)
{
    nfdchar_t* path = nullptr;
    nfdfilteritem_t filterItem[1] = {{"SC-Mod Replay", "screp"}};
    auto result = NFD_OpenDialog(&path, filterItem, 1, NULL);
    if (result == NFD_OKAY) {
        SCReplaySystem::get().getReplay().load(path);
        FLAlertLayer::create(nullptr, "Info", "Ok", nullptr, "Replay loaded.")->show();
        free(path);
    }
}