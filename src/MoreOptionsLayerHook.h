#pragma once

#include "includes.h"

class MoreOptionsLayerHook : public MoreOptionsLayer {
	public:
	static void LoadHooks();
	bool MoreOptionsLayerInit();
	static void OptionCheckUpdate();
    static void patchMemory(void* loc, std::vector<uint8_t>);
};