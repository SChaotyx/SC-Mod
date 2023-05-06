#include "GDPlayLayer.h"
#include "SCToolsLayer.h"
#include "SCToolBox.h"
#include "SCReplay.h"

void GDPlayLayer::Hook()
{
    matdash::add_hook<&GDPlayLayer::Init>(base + 0x1FB780);
    matdash::add_hook<&GDPlayLayer::Update, matdash::Thiscall>(base + 0x2029C0);
    matdash::add_hook<&GDPlayLayer::updateVisibility>(base + 0x205460);
    matdash::add_hook<&GDPlayLayer::onLevelComplete>(base + 0x1FD3D0);
    matdash::add_hook<&GDPlayLayer::onPauseGame>(base + 0x20D3C0);
    matdash::add_hook<&GDPlayLayer::onReset>(base + 0x20BF00);
    matdash::add_hook<&GDPlayLayer::onQuit>(base + 0x20D810);

    matdash::add_hook<&GDPlayLayer::onPushButton>(base + 0x111500);
    matdash::add_hook<&GDPlayLayer::onReleaseButton>(base + 0x111660);
}

bool GDPlayLayer::Init(GJGameLevel* level)
{

    matdash::orig<&GDPlayLayer::Init>(this, level);

    SCReplaySystem::get().onReset();

    return true;
}

void GDPlayLayer::Update(float dt)
{
    SCReplaySystem::playHandler();
    matdash::orig<&GDPlayLayer::Update, matdash::Thiscall>(this, dt);
}

void GDPlayLayer::updateVisibility()
{
    matdash::orig<&GDPlayLayer::updateVisibility>(this);
}

void GDPlayLayer::onLevelComplete()
{
    matdash::orig<&GDPlayLayer::onLevelComplete>(this);
    SCReplaySystem::get().setReplayMode(ReplayState::NONE);
	if(PlayLayer::get()->m_level->m_eLevelType == kGJLevelTypeEditor ) SCToolsLayer::resetOnQuit();
}

void GDPlayLayer::onPauseGame(bool idk)
{
    matdash::orig<&GDPlayLayer::onPauseGame>(this, idk);
}

void GDPlayLayer::onReset()
{
    matdash::orig<&GDPlayLayer::onReset>(this);
    SCReplaySystem::get().onReset();
    float levelSpeed = CCDirector::sharedDirector()->getScheduler()->getTimeScale();
	if(levelSpeed != 1)SCToolBox::setSongPitch(levelSpeed);
}

void GDPlayLayer::onQuit()
{
    matdash::orig<&GDPlayLayer::onQuit>(this);
    SCReplaySystem::get().setReplayMode(ReplayState::NONE);
	if(PlayLayer::get()->m_level->m_eLevelType == kGJLevelTypeEditor ) SCToolsLayer::resetOnQuit();
}

void GDPlayLayer::onPushButton(PlayLayer* self, int idk, bool button)
{
    if(idk == 1) return matdash::orig<&GDPlayLayer::onPushButton>(self, idk, button);
    if (SCReplaySystem::recordHandler(true, button)) return;
    matdash::orig<&GDPlayLayer::onPushButton>(self, idk, button);
}

void GDPlayLayer::onReleaseButton(PlayLayer* self, int idk, bool button)
{
    if(idk == 1) return matdash::orig<&GDPlayLayer::onReleaseButton>(self, idk, button);
    if (SCReplaySystem::recordHandler(false, button)) return;
    matdash::orig<&GDPlayLayer::onReleaseButton>(self, idk, button);
}