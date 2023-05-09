#include "SCReplay.h"
#include "GDPlayLayer.h"
#include <fstream>

bool SCReplaySystem::recordHandler(bool hold, bool button)
{
    if (GameManager::sharedState()->getPlayLayer()) {
        auto& RS = SCReplaySystem::get();
        if (RS.isPlaying()) return true;
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
    if(!isRecording()) return;
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
    } else if(isRecording()) {
        auto PL = GameManager::sharedState()->getPlayLayer();
        bool hasCheckpoints = PL->m_checkpoints->count();
        const auto checkpoint = practiceFix.getLastCheckpoint();
        const auto& actions = SCReplay.getActions();
        if (!hasCheckpoints) {
            frameOffset = 0;
            SCReplay.removeActions(getFrame());
        } else {
            frameOffset = checkpoint.frame;
            if (actions.back().hold) {
                SCReplay.removeActions(getFrame());
                recordAction(true, true);
            }
        }
    }
}




template <typename T, typename R>
T cast(R const v) { return reinterpret_cast<T>(v); }

template <typename T>
inline void bin_write(std::ofstream& stream, T value) {
	stream.write(cast<char*>(&value), sizeof(T));
}

template <typename T>
inline T bin_read(std::ifstream& stream) {
	T value;
	stream.read(cast<char*>(&value), sizeof(T));
	return value;
}

std::wstring widen(const char* str) {
    int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    if (size <= 0) {  }
    auto buffer = new wchar_t[size];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, buffer, size);
    std::wstring result(buffer, size_t(size) - 1);
    delete[] buffer;
    return result;
}

inline auto widen(const std::string& str) { return widen(str.c_str()); }

void SCReplay::save(const std::string& path)
{
    std::ofstream file;
	file.open(widen(path), std::ios::binary | std::ios::out);
    int nActions = 0;
	for (const auto& action : actions) {
		uint8_t hold = static_cast<uint8_t>(action.hold) | static_cast<uint8_t>(action.holdP2) << 1;
		bin_write(file, action.frame);
		file << hold;
        ++ nActions;
	}
	file.close();
    std::cout << "Saved " << nActions << " actions." << std::endl;
}

void SCReplay::load(const std::string& path)
{
    removeActions(0);
    std::ifstream file;
	file.open(widen(path), std::ios::binary | std::ios::in);
	file.seekg(0, std::ios::end);
	size_t file_size = static_cast<size_t>(file.tellg());
	file.seekg(0);
    size_t left = file_size - static_cast<size_t>(file.tellg());
    unsigned frame;
    uint8_t player;
    int nActions = 0;
	for (size_t _ = 0; _ < left / 5; ++_) {
        frame = bin_read<unsigned>(file);
		player = bin_read<uint8_t>(file);
        Action action;
        action.frame = frame;
        action.hold = player & 1;
        action.holdP2 = player & 2;
		addAction(action);
        ++ nActions;
	}
    file.close();
    std::cout << "loaded " << nActions << " actions." << std::endl;
}

void SCReplay::removeActions(unsigned frame)
{
    const auto check = [&](const Action& action) -> bool {
		return action.frame >= frame;
    };
	actions.erase(std::remove_if(actions.begin(), actions.end(), check), actions.end());
}