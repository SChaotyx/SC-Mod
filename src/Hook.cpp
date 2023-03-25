#include "Hooks.h"

#include "GDMenuLayer.h"
#include "GDMoreOptionsLayer.h"
#include "GDEditLevelLayer.h"
#include "GDPauseLayer.h"
#include "GDPlayLayer.h"
#include "GDLevelCompleteLayer.h"
#include "GDOptionsLayer.h"


void Hooks::Load() {

    GDMenuLayer::Hook();
    GDPlayLayer::Hook();
    GDPauseLayer::Hook();
    GDLevelCompleteLayer::Hook();
    GDEditLevelLayer::Hook();
    //GDMoreOptionsLayer::Hook();
    GDOptionsLayer::Hook();

}