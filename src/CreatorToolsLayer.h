#pragma once

#include "includes.h"

class CreatorToolsLayer : public gd::FLAlertLayer, public gd::FLAlertLayerProtocol {
    public:
    static CreatorToolsLayer* create() {
        auto pRet = new CreatorToolsLayer();
        if(pRet && pRet->init()) {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }

    bool init();
    void openCallback(CCObject*);
    void closeCallback(CCObject*) { keyBackClicked(); }

    void keyBackClicked();
    void keyDown(enumKeyCodes key) {
        if (key == 27) keyBackClicked();
    }

    void setLevelSpeed1(CCObject*);
    void setLevelSpeed2(CCObject*);
    void setLevelSpeed3(CCObject*);
    void setLevelSpeed4(CCObject*);
    static void applyLevelSpeed(float levelSpeed);

    void toggleNoclip(CCObject*);
    static void noclipToggler();
    auto noclipCheck(CCSprite*, CCSprite*);

    static void resetOnQuit();
};