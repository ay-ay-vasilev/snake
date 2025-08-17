#include "HighscoreManager.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

void score::HighscoreManager::loadHighscores()
{
	const auto fileName = "../res/data/highscores.json";

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "HighscoreManager: Failed to open" << fileName << std::endl;
		return;
	}

	nlohmann::json highscoresJson;
	file >> highscoresJson;


	if (const auto& recordsData = highscoresJson.find("records"); recordsData != highscoresJson.end())
	{
		for (const auto& recordData : *recordsData)
		{
			highscores[recordData["name"].get<std::string>()] = recordData["score"].get<int>();
		}
	}
}

void score::HighscoreManager::saveHighscores()
{
	const auto fileName = "../res/data/highscores.json";

	std::ofstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "HighscoreManager: Failed to open: " << fileName << std::endl;
		return;
	}

	nlohmann::json highscoresJson;
	for (const auto& record : highscores)
	{
		nlohmann::json recordJson;
		recordJson["name"] = record.first;
		recordJson["score"] = record.second;
		highscoresJson["records"].push_back(recordJson);
	}

	file << std::setw(4) << highscoresJson << std::endl;
}

void score::HighscoreManager::addHighscore(std::string name, int score)
{
	highscores[name] = score;
}

std::unordered_map<std::string, int> score::HighscoreManager::getHighscores() const
{
	return highscores;
}
