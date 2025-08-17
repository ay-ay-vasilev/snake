#pragma once
#include <unordered_map>
#include <string>

namespace score
{
class HighscoreManager
{
public:
	HighscoreManager() = default;

	void loadHighscores();
	void saveHighscores();

	void addHighscore(std::string name, int score);
	std::unordered_map<std::string, int> getHighscores() const;
private:
	std::unordered_map<std::string, int> highscores;
};
}
