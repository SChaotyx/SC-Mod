#include "SCToolBox.h"
#include "SCToolsLayer.h"



void SCToolBox::patchMemory(void* patchLoc, std::vector<uint8_t> bytes) {
    DWORD old_prot;
    VirtualProtect(patchLoc, bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot);
    memcpy(patchLoc, bytes.data(), bytes.size());
    VirtualProtect(patchLoc, bytes.size(), old_prot, &old_prot);
    //std::cout << "Applied Patch to " << patchLoc << std::endl;
}

#define public_cast(value, member) [](auto* v) { \
	class FriendClass__; \
	using T = std::remove_pointer<decltype(v)>::type; \
	class FriendeeClass__: public T { \
	protected: \
		friend FriendClass__; \
	}; \
	class FriendClass__ { \
	public: \
		auto& get(FriendeeClass__* v) { return v->member; } \
	} c; \
	return c.get(reinterpret_cast<FriendeeClass__*>(v)); \
}(value)

const char* SCToolBox::getTextureNameForSpriteFrame(cocos2d::CCSprite* sprite_node) {	
	auto* texture = sprite_node->getTexture();
	cocos2d::CCDictElement* el;		
	auto* frame_cache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
	auto* cached_frames = public_cast(frame_cache, m_pSpriteFrames);
	const auto rect = sprite_node->getTextureRect();
	cocos2d::CCDICT_FOREACH(cached_frames, el) {
		auto* frame = static_cast<cocos2d::CCSpriteFrame*>(el->getObject());
		if (frame->getTexture() == texture && frame->getRect().equals(rect)) {
			return el->getStrKey();
		}
	}
	return "";
}

void SCToolBox::setLevelSpeed(float levelSpeed) {
	auto dir = CCDirector::sharedDirector();
    dir->getScheduler()->setTimeScale(levelSpeed);
    SCToolBox::setSongPitch(levelSpeed);
    std::cout << "set time scale to: " << levelSpeed << std::endl;
}

void SCToolBox::setSongPitch(float pitch) {
    auto fmod = FMODAudioEngine::sharedEngine();
    if(fmod->isBackgroundMusicPlaying()) {
        auto channel = fmod->m_pGlobalChannel;
        __asm {
            push pitch;
            push channel;
        }
        SCToolBox::FMOD_Channel_setPitch();
    }
}