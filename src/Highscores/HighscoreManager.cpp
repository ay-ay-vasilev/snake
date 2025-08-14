#include "HighscoreManager.hpp"

void score::HighscoreManager::loadHighscores()
{
}

void score::HighscoreManager::saveHighscores()
{
}


const std::unordered_map<std::string, int>& score::HighscoreManager::getHighscores() const
{
	return highscores;
}
