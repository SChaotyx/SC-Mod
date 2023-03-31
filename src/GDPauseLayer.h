#pragma once

#include "includes.h"

class GDPauseLayer : public PauseLayer {
public:
    static void Hook();
	bool Init();
	bool onEditor(PlayLayer*);
	bool onResume(PlayLayer*);

    static FLAlertLayer* CreateLevelInfoLayer(GJGameLevel*);
	void levelInfoLayer(CCObject*);

    static FLAlertLayer* CreateLevelLeaderboardLayer(GJGameLevel*);
	void levelLeaderboardLayer(CCObject*);

	void optionsLayer(CCObject*);

	void challengesLayer(CCObject*);

	void extraOptLayer(CCObject*);

	void CreatorOpt(CCObject*);
};