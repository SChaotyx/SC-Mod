#include "includes.h"

class GDGameSoundManager : public GameSoundManager
{
    public:
    static void Hook();
    void playBGMusic(bool, bool, std::string);
};