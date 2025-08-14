#pragma once

#include "../Data/DataManager.hpp"
#include "../Options/OptionsManager.hpp"
#include "../Highscores/HighscoreManager.hpp"

#include <memory>

namespace context
{
class GameContext
{
public:
	GameContext();
	std::unique_ptr<data::DataManager>& getDataManager();
	std::unique_ptr<options::OptionsManager>& getOptionsManager();
	std::unique_ptr<score::HighscoreManager>& getHighscoreManager();

private:
	std::unique_ptr<data::DataManager> m_dataManager{};
	std::unique_ptr<options::OptionsManager> m_optionsManager{};
	std::unique_ptr<score::HighscoreManager> m_highscoreManager{};
};
}
