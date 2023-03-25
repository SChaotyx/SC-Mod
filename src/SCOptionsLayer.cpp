#include "SCOptionsLayer.h"
#include "SCManager.h"

bool SCOptionsLayer::Init() {
    if(!initWithColor(ccc4(0, 0, 0, 130))) return false;

    auto dir = CCDirector::sharedDirector();
    auto winSize = dir->getWinSize();

    m_pLayer = CCLayer::create();
    addChild(m_pLayer);

    m_pButtonMenu = CCMenu::create();
    m_pButtonMenu->setPosition(winSize.width / 2, winSize.height / 2);
    m_pLayer->addChild(m_pButtonMenu, 10);

    auto bg = extension::CCScale9Sprite::create("GJ_square02.png", {0, 0, 80, 80});
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

    SCOptionsLayer::createToggle("Practice Music", "6000", "Plays the level's song in-sync with your position, instead of the standard practice song.");
    SCOptionsLayer::createToggle("No Transition", "6001", "Shorterns scene transition time to 0s.");
    SCOptionsLayer::createToggle("Text Bypass", "6002", "Allows for unlimited text length in text inputs & Lets you input any character in all text inputs.");
    SCOptionsLayer::createToggle("Hide Attempts", "6003", "Hides the attempt count in-game.");
    SCOptionsLayer::createToggle("Slider Limit", "6004", "Lets sliders be dragged beyond the visible limit.");
    SCOptionsLayer::createToggle("Free Window Resize", "6005", "Removes limits in place for window resizing.");
    //SCOptionsLayer::createToggle("Disable SC-Mod Options", "6006", "Recommended if you have Mega Hack or some other mod menu.");
    
    setTouchEnabled(true);
    setKeypadEnabled(true);

    return true;
}

void SCOptionsLayer::openCallback(CCObject*) {
    auto menu = create();
    auto dir = CCDirector::sharedDirector();
    auto scene = dir->getRunningScene();
    menu->show();
    menu->registerWithTouchDispatcher();
    dir->getTouchDispatcher()->incrementForcePrio(2);

}

void SCOptionsLayer::keyBackClicked() {
    FLAlertLayer::keyBackClicked();
}

void SCOptionsLayer::createToggle(const char* name, const char* optionKey, const char* desc) {
    CCMenuItemToggler* toggleBtn;
    auto* const checkOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    auto* const checkOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

    float defX = -160;
    float defY = 80 - (toggleCount * 47);
    //xD
    if(toggleCount >= 3){
        defX = 25;
        defY = 80 - ((toggleCount - 3) * 47);
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

    toggleCount ++;
}

void SCOptionsLayer::onToggle(CCObject* sender){
    sender->retain();
    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    SCOptionsLayer::SettingToggler(static_cast<CCString*>(button->getUserData())->getCString());
}

CCSprite* SCOptionsLayer::toggleCheck(CCSprite* onSprite, CCSprite* offSprite, const char* optionKey) {
    bool GVariable = GameManager::sharedState()->getGameVariable(optionKey);
    return (GVariable) ? onSprite : offSprite;
}

void SCOptionsLayer::SettingToggler(const char* optionKey) {
    bool GVariable = GameManager::sharedState()->getGameVariable(optionKey);
    GVariable = !GVariable;
    if(GVariable) {
        //std::cout << "Gamevariable Enable Action in " << optionKey << std::endl;
        SCManager::enablePatch(optionKey);
    } else {
        //std::cout << "Gamevariable Disable Action in " << optionKey << std::endl;
        SCManager::disablePatch(optionKey);
    }
    GameManager::sharedState()->setGameVariable(optionKey, GVariable);
}