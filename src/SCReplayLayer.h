#pragma once

#include "includes.h"

class SCReplayLayer : public FLAlertLayer, public FLAlertLayerProtocol
{
    protected:
    float toggleCount = 0;

    public:
    static SCReplayLayer* create()
    {
        auto pRet = new SCReplayLayer();
        if(pRet && pRet->Init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }

    bool Init();
    void openCallback(CCObject*);
    void closeCallback(CCObject*) { keyBackClicked(); }
    void keyBackClicked();
    void keyDown(enumKeyCodes key) { if (key == 27) keyBackClicked(); }
    void recordCallback(CCObject*);
    void playingCallback(CCObject*);
    void onSave(CCObject*);
    void onLoad(CCObject*);
    void openRepFolder(CCObject*);

    void createToggle(const char*, const char*, const char*);
    void onToggle(CCObject*);
    CCSprite* toggleCheck(CCSprite*, CCSprite*, const char*);
    void SettingToggler(const char*);
    void toggleInfo(CCObject*);
};

