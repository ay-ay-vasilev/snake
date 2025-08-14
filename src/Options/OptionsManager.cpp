#include "OptionsManager.hpp"

#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

options::Color getColorFromJson(const nlohmann::json& json)
{
	return
		{
			json["r"].get<int>(),
			json["g"].get<int>(),
			json["b"].get<int>(),
			json["a"].get<int>()
		};
}

static void saveColorToJson(const options::Color& color, nlohmann::json& json)
{
	json["r"] = color.r;
	json["g"] = color.g;
	json["b"] = color.b;
	json["a"] = color.a;
}

void options::OptionsManager::setWindow(SDL_Window* window)
{
	m_window = window;
}

void options::OptionsManager::loadOptions()
{
	loadOptionPresets();
	loadUserOptions();
}

void options::OptionsManager::loadOptionPresets()
{
	const auto fileName = "../res/config/options_presets.json";

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "OptionsManager: Failed to open options presets file: " << fileName << std::endl;
		return;
	}

	nlohmann::json optionPresetsJson;
	file >> optionPresetsJson;


	if (const auto& resolutionsData = optionPresetsJson.find("resolutions"); resolutionsData != optionPresetsJson.end())
	{
		for (const auto& resolutionData : *resolutionsData)
		{
			Resolution resolution;
			resolution.name = (resolutionData)["name"].get<std::string>();
			resolution.width = (resolutionData)["width"].get<int>();
			resolution.height = (resolutionData)["height"].get<int>();
			m_resolutionPresets[resolution.name] = resolution;
		}
	}

	if (const auto& gameSpeedsData = optionPresetsJson.find("game_speeds"); gameSpeedsData != optionPresetsJson.end())
	{
		for (const auto& gameSpeedData : *gameSpeedsData)
		{
			GameSpeed gameSpeed;
			gameSpeed.name = (gameSpeedData)["name"].get<std::string>();
			gameSpeed.frameStep = (gameSpeedData)["frame_step"].get<int>();
			m_gameSpeedPresets[gameSpeed.name] = gameSpeed;
		}
	}

	if (const auto& defaultOptionsData = optionPresetsJson.find("default"); defaultOptionsData != optionPresetsJson.end())
	{
		m_defaultResolution.name = (*defaultOptionsData)["resolution"].get<std::string>();
		m_defaultResolution.width = m_resolutionPresets[m_defaultResolution.name].width;
		m_defaultResolution.height = m_resolutionPresets[m_defaultResolution.name].height;

		if (!m_isFullscreen)
			m_isFullscreen = (*defaultOptionsData)["fullscreen"].get<bool>();
		m_defaultFullscreen = m_isFullscreen.value();

		m_defaultSnake1Color = getColorFromJson((*defaultOptionsData)["snake_1_color"]);
		m_defaultSnake2Color = getColorFromJson((*defaultOptionsData)["snake_2_color"]);

		m_defaultGameSpeed = m_gameSpeedPresets.at((*defaultOptionsData)["game_speed"].get<std::string>());
		if (m_gameSpeed.name.empty())
			m_gameSpeed = m_defaultGameSpeed;
	}
}

void options::OptionsManager::loadUserOptions()
{
	const auto fileName = "../res/config/user_config.json";

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "OptionsManager: Failed to open user config file: " << fileName << std::endl;
		return;
	}

	nlohmann::json userOptionsJson;
	file >> userOptionsJson;

	if (const auto& resolutionData = userOptionsJson.find("resolution"); resolutionData != userOptionsJson.end())
	{
		const auto& resolutionName = (*resolutionData).get<std::string>();
		m_currentResolution = m_resolutionPresets[resolutionName];
	}
	if (const auto& fullscreenData = userOptionsJson.find("fullscreen"); fullscreenData != userOptionsJson.end())
	{
		m_isFullscreen = (*fullscreenData).get<bool>();
	}
	if (const auto& snake1ColorData = userOptionsJson.find("snake_1_color"); snake1ColorData != userOptionsJson.end())
	{
		m_snake1Color = getColorFromJson(*snake1ColorData);
	}
	if (const auto& snake2ColorData = userOptionsJson.find("snake_2_color"); snake2ColorData != userOptionsJson.end())
	{
		m_snake2Color = getColorFromJson(*snake2ColorData);
	}
	if (const auto& gameSpeedData = userOptionsJson.find("game_speed"); gameSpeedData != userOptionsJson.end())
	{
		m_gameSpeed = m_gameSpeedPresets.at((*gameSpeedData).get<std::string>());
	}
}

void options::OptionsManager::saveOptions()
{
	const auto fileName = "../res/config/user_config.json";

	std::ofstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "OptionsManager: Failed to open: " << fileName << std::endl;
		return;
	}

	nlohmann::json userOptionsJson;
	userOptionsJson["resolution"] = m_currentResolution.name;
	userOptionsJson["fullscreen"] = m_isFullscreen ? m_isFullscreen.value() : false;

	saveColorToJson(m_snake1Color, userOptionsJson["snake_1_color"]);
	saveColorToJson(m_snake2Color, userOptionsJson["snake_2_color"]);

	userOptionsJson["game_speed"] = m_gameSpeed.name;

	file << std::setw(4) << userOptionsJson << std::endl;
}

void options::OptionsManager::resetOptions()
{
	m_currentResolution = m_defaultResolution;
	m_isFullscreen = m_defaultFullscreen;
	m_snake1Color = m_defaultSnake1Color;
	m_snake2Color = m_defaultSnake2Color;
	m_gameSpeed = m_defaultGameSpeed;
}

options::Resolution options::OptionsManager::getCurrentResolution() const
{
	return m_currentResolution;
}

std::unordered_map<std::string, options::Resolution> options::OptionsManager::getResolutionPresets() const
{
	return m_resolutionPresets;
}

void options::OptionsManager::setCurrentResolution(options::Resolution newResolution)
{
	m_currentResolution = newResolution;
}

bool options::OptionsManager::getIsFullscreen() const
{
	return m_isFullscreen ? m_isFullscreen.value() : false;
}

void options::OptionsManager::setIsFullscreen(bool value)
{
	m_isFullscreen = value;
}

options::Color options::OptionsManager::getSnake1Color() const
{
	return m_snake1Color;
}

void options::OptionsManager::setSnake1Color(options::Color color)
{
	m_snake1Color = color;
}

options::Color options::OptionsManager::getSnake2Color() const
{
	return m_snake2Color;
}

void options::OptionsManager::setSnake2Color(options::Color color)
{
	m_snake2Color = color;
}

void options::OptionsManager::applyCurrentResolution()
{
	SDL_SetWindowFullscreen(m_window, m_isFullscreen ? m_isFullscreen.value() : false);
	SDL_SetWindowSize(m_window, m_currentResolution.width, m_currentResolution.height);
	centerWindow();
}

void options::OptionsManager::centerWindow()
{
	SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

std::unordered_map<std::string, options::GameSpeed> options::OptionsManager::getGameSpeedPresets() const
{
	return m_gameSpeedPresets;
}

std::vector<std::string> options::OptionsManager::getGameSpeedPresetsStr() const
{
	std::vector<std::string> result;
	for (const auto& gameSpeed : m_gameSpeedPresets)
	{
		result.emplace_back(gameSpeed.first);
	}
	return result;
}

options::GameSpeed options::OptionsManager::getGameSpeed() const
{
	return m_gameSpeed;
}

std::string options::OptionsManager::getGameSpeedStr() const
{
	return m_gameSpeed.name;
}

void options::OptionsManager::setGameSpeed(options::GameSpeed gameSpeed)
{
	m_gameSpeed = gameSpeed;
}

void options::OptionsManager::setGameSpeed(std::string gameSpeed)
{
	m_gameSpeed = m_gameSpeedPresets.at(gameSpeed);
}
