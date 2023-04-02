#include "GDMoreOptionsLayer.h"

void GDMoreOptionsLayer::Hook()
{
    matdash::add_hook<&GDMoreOptionsLayer::Init>(base + 0x1DE8F0);
}

bool GDMoreOptionsLayer::Init()
{
    matdash::orig<&GDMoreOptionsLayer::Init>(this);
    return true;
}