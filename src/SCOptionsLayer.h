#pragma once

#include "includes.h"

class SCOptionsLayer : public gd::FLAlertLayer, public gd::FLAlertLayerProtocol
{
    protected:
    float toggleCount = 0;

    public:
    static SCOptionsLayer* create()
    {
        auto pRet = new SCOptionsLayer();
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
    void createToggle(const char*, const char*, const char*);
    void onToggle(CCObject*);
    CCSprite* toggleCheck(CCSprite*, CCSprite*, const char*);
    void SettingToggler(const char*);
};