#include "HighscoreManager.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>

namespace score::defaults
{
	constexpr int maxHighscoreCount = 10;
	std::filesystem::path resDir = RES_DIR;
	const std::string highscoreFileName = resDir / "data/highscores.dat";
}

void score::HighscoreManager::loadHighscores()
{
	using namespace score::defaults;
	std::ifstream file(highscoreFileName, std::ios::binary);
	if (!file)
	{
		std::cerr << "Error opening file: " << highscoreFileName << "\n";
		return;
	}
    uint32_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    m_highscores.resize(count);
	for (uint32_t i = 0; i < count; i++) {
		uint32_t nameLen;
		file.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));

		std::string name(nameLen, '\0');
		file.read(&name[0], nameLen);

		int score;
		file.read(reinterpret_cast<char*>(&score), sizeof(score));

		m_highscores[i] = { name, score };
	}

    uint32_t storedChecksum;
    file.read(reinterpret_cast<char*>(&storedChecksum), sizeof(storedChecksum));

    uint32_t computedChecksum = computeChecksum();
    if (storedChecksum != computedChecksum) {
		throw std::runtime_error("Highscore file has been corrupted!\n");
        return;
    }
	sortHighscores();
}

void score::HighscoreManager::saveHighscores()
{
	using namespace score::defaults;
	std::ofstream file(highscoreFileName, std::ios::binary);
	if (!file)
	{
		std::cerr << "Error opening file: " << highscoreFileName << "\n";
		return;
	}

	uint32_t count = m_highscores.size();
	file.write(reinterpret_cast<const char*>(&count), sizeof(count));

	for (auto& e : m_highscores) {
		uint32_t nameLen = e.name.size();
		file.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
		file.write(e.name.data(), nameLen);

		file.write(reinterpret_cast<char*>(&e.score), sizeof(e.score));
	}

	uint32_t checksum = computeChecksum();
	file.write(reinterpret_cast<const char*>(&checksum), sizeof(checksum));
}

void score::HighscoreManager::addHighscore(std::string name, int score)
{
	m_highscores.emplace_back(name, score);
	sortHighscores();
	if (m_highscores.size() > score::defaults::maxHighscoreCount)
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

uint32_t score::HighscoreManager::computeChecksum()
{
	uint32_t checksum = 0;
	for (const auto& e : m_highscores)
	{
		for (char c : e.name) checksum += static_cast<unsigned char>(c);
		checksum += static_cast<uint32_t>(e.score);
	}
	return checksum;
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
	if (m_highscores.size() < score::defaults::maxHighscoreCount)
		return true;
	
	if (m_highscores.back().score < m_currentScore)
		return true;

	return false;
}
