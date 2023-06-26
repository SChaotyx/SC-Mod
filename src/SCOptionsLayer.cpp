#include "SCOptionsLayer.h"
#include "SCManager.h"
#include "nfd.hpp"

bool SCOptionsLayer::Init()
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
    auto btn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(SCOptionsLayer::closeCallback));
    btn->setPosition(-195,135);
    m_pButtonMenu->addChild(btn);

    auto label = CCLabelBMFont::create("SC-Options", "bigFont.fnt");
    label->setScale(0.8f);
    label->setPosition(0, 125);
    m_pButtonMenu->addChild(label);

    auto keysBtn = extension::CCScale9Sprite::create("GJ_button_04.png", {0, 0, 40, 40});
    keysBtn->setContentSize(CCSize(55,25));
    label = CCLabelBMFont::create("Keys", "goldFont.fnt");
    label->setScale(0.6f);
    label->setPosition(28, 14.5);
    keysBtn->addChild(label);
    btn = CCMenuItemSpriteExtra::create(keysBtn, this, menu_selector(SCOptionsLayer::keysInfo));
    btn->setPosition(165,120);
    m_pButtonMenu->addChild(btn);

    auto btnSpr = CCSprite::create("SC_ProfileBtn_001.png");
    btnSpr->setScale(0.5f);
    auto SCLogo = CCSprite::create("SC_SChaotyxBtn_001.png");
    SCLogo->setPosition({(btnSpr->getContentSize().width / 2) - 1, (btnSpr->getContentSize().height / 2) + 2});
    SCLogo->setScale(0.75f);
    btnSpr->addChild(SCLogo);
    btn = CCMenuItemSpriteExtra::create(
        btnSpr, this, menu_selector(SCOptionsLayer::onSCProfile)
    );
    btn->setPosition(120, 120);
    m_pButtonMenu->addChild(btn);

    label = CCLabelBMFont::create("v1.3.2", "bigFont.fnt");
    label->setScale(0.4f);
    label->setPosition(165, -125);
    m_pButtonMenu->addChild(label);

    SCOptionsLayer::createToggle("Practice Music", "Opt_practiceMusic", "Plays the level's song in-sync with your position, instead of the standard practice song.");
    SCOptionsLayer::createToggle("No Transition", "Opt_noTransition", "Shorterns scene transition time to 0s.");
    SCOptionsLayer::createToggle("Text Bypass", "Opt_textByPasses", "Allows for unlimited text length in text inputs & Lets you input any character in all text inputs.");
    SCOptionsLayer::createToggle("Hide Attempts", "Opt_hideAtts", "Hides the attempt count in-game.");
    SCOptionsLayer::createToggle("No Slider Limit", "Opt_noSliderLimit", "Lets sliders be dragged beyond the visible limit.");
    SCOptionsLayer::createToggle("Free Window Resize", "Opt_freeWinResize", "Removes limits in place for window resizing.");

    SCOptionsLayer::createToggle("No Speedhack Music", "Opt_noSpdHckMusic", "Speedhack affects music.");
    SCOptionsLayer::createToggle("Disable Keybinds", "Opt_disableKeybinds", "Disable SC-Mod keybinds during gameplay.");
    //SCOptionsLayer::createToggle("Custom Song Folder", "Opt_customSongfolder", "Set your custom song folder.[unfinished: download/detect song to custom folder]");

    setTouchEnabled(true);
    setKeypadEnabled(true);

    return true;
}

void SCOptionsLayer::openCallback(CCObject*)
{
    auto menu = create();
    auto dir = CCDirector::sharedDirector();
    auto scene = dir->getRunningScene();
    menu->show();
    menu->registerWithTouchDispatcher();
    dir->getTouchDispatcher()->incrementForcePrio(2);

}

void SCOptionsLayer::keyBackClicked()
{
    FLAlertLayer::keyBackClicked();
}

void SCOptionsLayer::createToggle(const char* name, const char* optionKey, const char* desc)
{
    CCMenuItemToggler* toggleBtn;
    auto* const checkOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    auto* const checkOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

    float defX, defY;

    if(fmod(toggleCount, 2) == 0) { 
        defX = -160;
        defY = 80 - ((toggleCount / 2) * 47);
    } else { 
        defX = 25;
        defY = 80 - (((toggleCount - 1) / 2) * 47);
    }

    toggleBtn = CCMenuItemToggler::create(
        SCOptionsLayer::toggleCheck(checkOn, checkOff, optionKey),
        SCOptionsLayer::toggleCheck(checkOff, checkOn, optionKey),
        this,
        menu_selector(SCOptionsLayer::onToggle));
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
            menu_selector(SCOptionsLayer::toggleInfo)
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

void SCOptionsLayer::onToggle(CCObject* sender)
{
    sender->retain();
    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    SCOptionsLayer::SettingToggler(static_cast<CCString*>(button->getUserData())->getCString());
}

CCSprite* SCOptionsLayer::toggleCheck(CCSprite* onSprite, CCSprite* offSprite, const char* optionKey)
{
    bool GVariable = SCManager::getSCModVariable(optionKey);
    return (GVariable) ? onSprite : offSprite;
}

void SCOptionsLayer::SettingToggler(const char* optionKey)
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

void SCOptionsLayer::toggleInfo(CCObject* sender)
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

void SCOptionsLayer::keysInfo(CCObject*)
{
    auto layer = FLAlertLayer::create(
        nullptr, "SC-Mod Keys", "OK", nullptr,
        "<cg>[A]</c> - Reset level.\n<cy>[N]</c> - Toggle noclip\n(only local levels)."
    );
    layer->m_pTargetLayer = this;
    layer->show();
}

void SCOptionsLayer::onSCProfile(CCObject*)
{
    ProfilePage::create(4916065, false)->show();
}

void SCOptionsLayer::setSongFolder()
{
    NFD::UniquePath outPath;
    nfdresult_t result = NFD::PickFolder(outPath);
    if (result == NFD_OKAY) {
        SCManager::setSCModString("Opt_customSongfolderPath", outPath.get());
    }
}