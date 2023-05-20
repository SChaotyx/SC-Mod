#include "SCReplayLayer.h"
#include "SCReplay.h"
#include <nfd.h>
#include <shellapi.h>

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

    sprite = CCSprite::createWithSpriteFrameName("gj_folderBtn_001.png");
    btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCReplayLayer::openRepFolder));
    btn->setPosition(170,-115);
    m_pButtonMenu->addChild(btn);

    SCReplayLayer::createToggle("Auto record/save", "Replay_RecAll", "Replays automatically saved to default folder every time you complete a level (except practice mode and local levels).");

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

void SCReplayLayer::openRepFolder(CCObject*)
{
    std::string folder = "SCReplays";
    if (!std::filesystem::is_directory(folder) || !std::filesystem::exists(folder))
        std::filesystem::create_directory(folder);
    ShellExecuteA(NULL, "open", "SCReplays\\", NULL, NULL, SW_SHOWDEFAULT);
}

void SCReplayLayer::createToggle(const char* name, const char* optionKey, const char* desc)
{
    CCMenuItemToggler* toggleBtn;
    auto* const checkOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    auto* const checkOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

    float defX, defY;

    if(fmod(toggleCount, 2) == 0) { 
        defX = -160;
        defY = (80 - 47) - ((toggleCount / 2) * 47);
    } else { 
        defX = 25;
        defY = (80 - 47) - (((toggleCount - 1) / 2) * 47);
    }

    toggleBtn = CCMenuItemToggler::create(
        SCReplayLayer::toggleCheck(checkOn, checkOff, optionKey),
        SCReplayLayer::toggleCheck(checkOff, checkOn, optionKey),
        this,
        menu_selector(SCReplayLayer::onToggle));
    toggleBtn->setScale(0.8f);
    toggleBtn->setPosition(defX, defY);
    toggleBtn->setSizeMult(1.2f);
    m_pButtonMenu->addChild(toggleBtn);

    auto label = CCLabelBMFont::create(name, "bigFont.fnt");
    label->setScale(0.4f);
    label->setPosition((defX + 25), (defY));
    label->setAnchorPoint({0,0.5f});
    m_pButtonMenu->addChild(label);

    auto optionString = CCString::create(optionKey);
    optionString->retain();
    toggleBtn->setUserData(optionString);

    if(!strcmp(desc, "") == 0)
    {
        auto infosprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        auto infobtn = CCMenuItemSpriteExtra::create(
            infosprite,
            this,
            menu_selector(SCReplayLayer::toggleInfo)
        );
        infobtn->setPosition(defX - 17,defY + 17);
        infobtn->setScale(0.5f);
        infobtn->m_fBaseScale = 0.5f;
        m_pButtonMenu->addChild(infobtn);

        auto infoString = CCString::create(desc);
        infoString->retain();
        infobtn->setUserData(infoString);
    }

    toggleCount ++;
}

void SCReplayLayer::onToggle(CCObject* sender)
{
    sender->retain();
    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    SCReplayLayer::SettingToggler(static_cast<CCString*>(button->getUserData())->getCString());
}

CCSprite* SCReplayLayer::toggleCheck(CCSprite* onSprite, CCSprite* offSprite, const char* optionKey)
{
    bool GVariable = SCManager::getSCModVariable(optionKey);
    return (GVariable) ? onSprite : offSprite;
}

void SCReplayLayer::SettingToggler(const char* optionKey)
{
    bool GVariable = SCManager::getSCModVariable(optionKey);
    GVariable = !GVariable;
    if(GVariable) {
        SCManager::enablePatch(optionKey);
    } else {
        SCManager::disablePatch(optionKey);
    }
    SCManager::setSCModVariable(optionKey, GVariable);
}

void SCReplayLayer::toggleInfo(CCObject* sender)
{
    sender->retain();
    auto info = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto layer = FLAlertLayer::create(
        nullptr, "Info", "OK", nullptr,
        static_cast<CCString*>(info->getUserData())->getCString()
    );
    layer->m_pTargetLayer = this;
    layer->show();
}