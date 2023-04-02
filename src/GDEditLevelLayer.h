#pragma once

#include "includes.h"

class GDEditLevelLayer : public EditLevelLayer
{
	public:
    static void Hook();
	bool Init(GJGameLevel*);

    static FLAlertLayer* CreateLevelInfoLayer(GJGameLevel*);
	void levelInfoLayer(CCObject*);

    static FLAlertLayer* CreateLevelLeaderboardLayer(GJGameLevel*);
	void levelLeaderboardLayer(CCObject*);
};