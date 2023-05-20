#include "SCReplay.h"
#include "GDPlayLayer.h"

bool SCReplaySystem::recordHandler(bool hold, bool button)
{
    if (auto PL = GameManager::sharedState()->getPlayLayer()) {
        auto& RS = SCReplaySystem::get();
        if (RS.isPlaying()) return true;
        if(!PL->m_hasCompletedLevel)
            RS.recordAction(hold, button);
    }
    return false;
}

void SCReplaySystem::playHandler()
{
    auto& RS = SCReplaySystem::get();
    if(RS.state == ReplayState::NONE) return;
    if(RS.state == ReplayState::PLAYING) {
        RS.playAction();
        return;
    }
}

void SCReplaySystem::recordAction(bool hold, bool button)
{
    if(!isRecording() && !isRecAll()) return;
    auto GM = GameManager::sharedState();
    auto isTwoPlayer = PlayLayer::get()->m_level->m_bTwoPlayerMode;
    bool flip = true;
    button ^= flip && GM->getGameVariable("0010");
    Action action;
    action.hold = hold;
    action.holdP2 = isTwoPlayer && !button;
    action.frame = getFrame();
    SCReplay.addAction(action);
    std::cout << "record p1: " << action.hold << " p2: " << action.holdP2 << " at frame: " << action.frame << std::endl;
}

void SCReplaySystem::playAction()
{
    auto GM = GameManager::sharedState();
    auto PL = GM->getPlayLayer();
    auto flip = GM->getGameVariable("0010");
    auto& actions = SCReplay.getActions();
    Action action;
    while (action_index < actions.size() && getFrame() >= (action = actions[action_index]).frame) {
        if (action.hold) {
            std::cout << "action N: " << action_index << " frame " << action.frame << " hold " << std::endl;
            reinterpret_cast<void(__thiscall*)(PlayLayer*, int, bool)>(base + 0x111500)(PL, 1, !action.holdP2 ^ flip);
        } else {
            std::cout << "action N: " << action_index << " frame " << action.frame << " release " << std::endl;
            reinterpret_cast<void(__thiscall*)(PlayLayer*, int, bool)>(base + 0x111660)(PL, 1, !action.holdP2 ^ flip);
        }
        ++action_index;
    }
}

unsigned SCReplaySystem::getFrame()
{
    auto PL = GameManager::sharedState()->getPlayLayer();
    if (PL != nullptr) return static_cast<unsigned>(PL->m_time * 60) + frameOffset;
    return 0;
}

void SCReplaySystem::onReset()
{
    if(isPlaying()) {
        action_index = 0;
        frameOffset = 0;
    } else if(isRecording() || isRecAll()) {
        auto PL = GameManager::sharedState()->getPlayLayer();
        bool hasCheckpoints = PL->m_checkpoints->count();
        const auto checkpoint = practiceFix.getLastCheckpoint();
        const auto& actions = SCReplay.getActions();
        if (!hasCheckpoints) {
            frameOffset = 0;
            SCReplay.removeActions(0);
        } else {
            frameOffset = checkpoint.frame;
            if (actions.back().hold) {
                SCReplay.removeActions(getFrame());
                recordAction(true, true);
            } else {
                SCReplay.removeActions(getFrame());
            }
        }
    }
}

GJGameLevel* getLevel()
{
    if(auto play_layer = GameManager::sharedState()->getPlayLayer()){
        return play_layer->get()->m_level;
    }
    return false;
}

void SCReplay::save(const std::string& path)
{
    std::ofstream file(path);
    int nActions = 0;
    file << "[HEADER]" << "\n";
    file << "Ver=" << REPVER << "\n";
    file << "FPS=" << 60 << "\n";
    file << "[ACTIONS]" << "\n";
    for (const auto& action : actions) {
        file << nActions << ":" << action.frame << ":" << action.hold << ":" << action.holdP2 << "\n";
        ++ nActions;
    }
    std::cout << "Saved " << nActions << " actions." << std::endl;
}

void SCReplay::load(const std::string& path)
{
    removeActions(0);
    std::ifstream file(path);
    std::string line;
    Action action;
    int nActions = 0;
    bool loadActions = false;

    while(std::getline(file, line)) {
        if (line.empty()) continue;
        if(loadActions) {

            int posInit = 0;
            int posFound = 0;
            std::string splitted;
            std::vector<std::string> results;
            while(posFound >= 0) {
                posFound = line.find(':', posInit);
                splitted = line.substr(posInit, posFound - posInit);
                posInit = posFound + 1;
                results.push_back(splitted);
            }
            action.frame = std::stoi(std::string(results[1]));
            action.hold = results[2] == "1";
            action.holdP2 = results[3] == "1";
            addAction(action);
            ++ nActions;
        }
        if(line == "[ACTIONS]") loadActions = true;
    }
    std::cout << "loaded " << nActions << " actions." << std::endl;
}

void SCReplay::removeActions(unsigned frame)
{
    const auto check = [&](const Action& action) -> bool {
		return action.frame >= frame;
    };
	actions.erase(std::remove_if(actions.begin(), actions.end(), check), actions.end());
}

void SCReplaySystem::autoSaveReplay(GJGameLevel* level)
{
    //[levelID][levelName][creatorName][date].screp
    if(!isRecAll() || isPlaying()) return;

    auto t = std::time(nullptr);
    std::tm tm {};
    localtime_s(&tm, &t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y-%H.%M.%S");
    auto date = oss.str();

    std::string levelID = std::to_string(level->m_nLevelID);
    std::string levelName = level->m_sLevelName;
    std::string creatorName = level->m_sCreatorName;
    std::string folder = "SCReplays";

    std::string path = 
        folder+"\\["+levelID+"]["+date+"]["+levelName+"]["+creatorName+"].screp";

    if (!std::filesystem::is_directory(folder) || !std::filesystem::exists(folder))
        std::filesystem::create_directory(folder);

    getReplay().save(path);
}