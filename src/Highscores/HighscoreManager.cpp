#include "HighscoreManager.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

namespace score::defaults
{
	constexpr int highscoreMaxSize = 10;
}

void score::HighscoreManager::loadHighscores()
{
	const auto fileName = "../res/data/highscores.json";

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return;
	}

	nlohmann::json highscoresJson;
	file >> highscoresJson;


	if (const auto& recordsData = highscoresJson.find("records"); recordsData != highscoresJson.end())
	{
		for (const auto& recordData : *recordsData)
		{
			const auto name = recordData["name"].get<std::string>();
			const auto score = recordData["score"].get<int>();
			m_highscores.emplace_back(name, score);
		}
	}
	sortHighscores();
}

void score::HighscoreManager::saveHighscores()
{
	const auto fileName = "../res/data/highscores.json";

	std::ofstream file(fileName);
	if (!file.is_open())
	{
		return;
	}

	nlohmann::json highscoresJson;
	for (const auto& record : m_highscores)
	{
		nlohmann::json recordJson;
		recordJson["name"] = record.name;
		recordJson["score"] = record.score;
		highscoresJson["records"].push_back(recordJson);
	}

	file << std::setw(4) << highscoresJson << std::endl;
}

void score::HighscoreManager::addHighscore(std::string name, int score)
{
	m_highscores.emplace_back(name, score);
	sortHighscores();
	if (m_highscores.size() > score::defaults::highscoreMaxSize)
		m_highscores.pop_back();
}

std::vector<score::ScoreRecord> score::HighscoreManager::getHighscores() const
{
	return m_highscores;
}

void score::HighscoreManager::sortHighscores()
{
	std::sort(m_highscores.begin(), m_highscores.end(),
		   [](auto& a, auto& b) {return a.score > b.score; });
}

const int score::HighscoreManager::getCurrentScore() const
{
	return m_currentScore;
}

void score::HighscoreManager::setCurrentScore(int value)
{
	m_currentScore = value;
}

bool score::HighscoreManager::isNewHighscore() const
{
	if (m_highscores.size() < score::defaults::highscoreMaxSize)
		return true;
	
	if (m_highscores.back().score < m_currentScore)
		return true;

	return false;
}
