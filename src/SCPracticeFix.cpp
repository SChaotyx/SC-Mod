#include "SCPracticeFix.h"
#include "SCReplay.h"

void SCCheckpointObject::saveInfo() {
    auto& RS = SCReplaySystem::get();
    m_checkpoint = RS.getPracticeFix().createCheckpoint();
}

Checkpoint SCPracticeFix::createCheckpoint() {
    auto PL = GameManager::sharedState()->getPlayLayer();
    if(PL) {
        auto& RS = SCReplaySystem::get();
        return {
            RS.getFrame()
        };
    } else {
        return {};
    }
}