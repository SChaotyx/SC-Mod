#pragma once

#include "includes.h"

class CreatorToolsLayer : public FLAlertLayer, public CCTextFieldDelegate, public FLAlertLayerProtocol {
    public:

    static auto create();
    virtual bool init();
   
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

    static void resetOnQuit();
    static void noclipToggler();
    void toggleNoclip(CCObject*);
    auto noclipTest(CCSprite*, CCSprite*);
};