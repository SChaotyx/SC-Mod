#pragma once
#include "includes.h"
#include "SCPracticeFix.h"

enum ReplayState
{
    NONE,
    RECORDING,
    PLAYING
};

struct Action {
    union {
        unsigned frame;
    };
	bool hold;
	bool holdP2;
};

class SCReplay 
{
protected:
    std::vector<Action> actions;

public:    
    void addAction(const Action& action) { actions.push_back(action); }
    auto& getActions() { return actions; }
    void removeActions(unsigned frame);

    void save(const std::string& path);
    void load(const std::string& path);
};

class SCReplaySystem
{
    SCReplay SCReplay;
    ReplayState state = NONE;
    size_t action_index = 0;
    SCPracticeFix practiceFix;
    unsigned frameOffset;

    public:
    static auto& get() { static SCReplaySystem instance; return instance; }

    static void playHandler();
    static bool recordHandler(bool, bool);

    void recordAction(bool, bool);
    void playAction();

    bool isRecording() { return state == RECORDING; }
    bool isPlaying() { return state == PLAYING; }

    inline auto& getReplay() { return SCReplay; }
    unsigned getFrame();
    inline auto& getPracticeFix() { return practiceFix; }

    void setReplayMode(ReplayState newState) { state = newState; }
    void onReset();

};