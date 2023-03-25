#include "GDPlayLayer.h"
#include "SCToolsLayer.h"

void GDPlayLayer::Hook() {
    matdash::add_hook<&GDPlayLayer::onQuit>(gd::base + 0x20D810);
    matdash::add_hook<&GDPlayLayer::onLevelComplete>(gd::base + 0x1FD3D0);
}

bool GDPlayLayer::onQuit() {
    if(!matdash::orig<&GDPlayLayer::onQuit>(this)) return false;
	if(PlayLayer::get()->m_level->m_eLevelType == 2 ) SCToolsLayer::resetOnQuit();
    return true;
}

bool GDPlayLayer::onLevelComplete() {
    if(!matdash::orig<&GDPlayLayer::onLevelComplete>(this)) return false;
	if(PlayLayer::get()->m_level->m_eLevelType == 2 ) SCToolsLayer::resetOnQuit();
    return true;
}