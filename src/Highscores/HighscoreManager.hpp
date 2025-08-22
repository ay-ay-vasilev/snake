#pragma once
#include <vector>
#include <string>

namespace score
{
struct ScoreRecord {
	std::string name;
	int score;
};

class HighscoreManager
{
public:
	HighscoreManager() = default;

	void loadHighscores();
	void saveHighscores();

	void addHighscore(std::string name, int score);
	std::vector<ScoreRecord> getHighscores() const;

	const int getCurrentScore() const;
	void setCurrentScore(int value);
private:
	void sortHighscores();
	std::vector<ScoreRecord> m_highscores;
	int m_currentScore{0};
};
}
