#pragma once

#include "includes.h"

class GDMenuLayer : public MenuLayer
{
    public:
    SimplePlayer* AccIconBtn;

    public:
    static void Hook();
    bool Init();
    void AccountIcon();
    int frameIcon(IconType);
};