#include "GDPlayLayer.h"
#include "SCToolsLayer.h"

void GDPlayLayer::Hook() {
    matdash::add_hook<&GDPlayLayer::onQuit>(base + 0x20D810);
    matdash::add_hook<&GDPlayLayer::onLevelComplete>(base + 0x1FD3D0);
}

bool GDPlayLayer::onQuit() {
    matdash::orig<&GDPlayLayer::onQuit>(this);
	if(PlayLayer::get()->m_level->m_eLevelType == 2 ) SCToolsLayer::resetOnQuit();
    return true;
}

bool GDPlayLayer::onLevelComplete() {
    matdash::orig<&GDPlayLayer::onLevelComplete>(this);
	if(PlayLayer::get()->m_level->m_eLevelType == 2 ) SCToolsLayer::resetOnQuit();
    return true;
}