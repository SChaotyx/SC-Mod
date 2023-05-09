#pragma once
#include "includes.h"
#include <stack>

struct Checkpoint {
    unsigned frame;
};

class SCCheckpointObject : public CheckpointObject {
    public:
    Checkpoint m_checkpoint;
    void saveInfo();
    static auto create() {
        auto ret = new SCCheckpointObject;
        if(ret && ret->init()) {
            ret->autorelease();
            ret->saveInfo();
        } else {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }
};

class SCPracticeFix {
    std::stack<Checkpoint> checkpoints;
    friend class SCReplaySystem;
public:
    Checkpoint createCheckpoint();

    Checkpoint getLastCheckpoint() {
        auto PL = GameManager::sharedState()->getPlayLayer();
        if(PL && PL->m_checkpoints->count()) {
            auto checkpointObj = dynamic_cast<SCCheckpointObject*>(PL->m_checkpoints->lastObject());
            if (checkpointObj) return checkpointObj->m_checkpoint;
        }
        return {};
    }
};

