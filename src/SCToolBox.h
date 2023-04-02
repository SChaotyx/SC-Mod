#pragma once

#include "includes.h"

namespace SCToolBox
{
    void patchMemory(void* loc, std::vector<uint8_t>);

	const char* getTextureNameForSpriteFrame(cocos2d::CCSprite* sprite_node);
    
    void setLevelSpeed(float);
    void setSongPitch(float);
    inline int (*FMOD_Channel_setPitch)();
};