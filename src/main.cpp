#include "includes.h"
#include <matdash/boilerplate.hpp>

#define DEBUG

#ifdef DEBUG
    #include <matdash/console.hpp>
#endif

#include "Hooks.h"

void mod_main(HMODULE)
{

    #ifdef DEBUG
        matdash::create_console();
    #endif

    Hooks::Load();

}