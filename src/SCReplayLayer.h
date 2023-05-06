#pragma once

#include "includes.h"

class SCReplayLayer : public FLAlertLayer, public FLAlertLayerProtocol
{
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
};

