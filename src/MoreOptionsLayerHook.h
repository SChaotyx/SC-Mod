#pragma once

#include "includes.h"

class MoreOptionsLayerHook : public MoreOptionsLayer {
	public:
	static void LoadHooks();
	bool MoreOptionsLayerInit();
	static void OptionCheckUpdate();
};