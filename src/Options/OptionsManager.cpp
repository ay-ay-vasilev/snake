#include "OptionsManager.hpp"

#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

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

	if (const auto& defaultOptionsData = optionPresetsJson.find("default"); defaultOptionsData != optionPresetsJson.end())
	{
		m_defaultResolution.name = (*defaultOptionsData)["resolution"].get<std::string>();
		m_defaultResolution.width = m_resolutionPresets[m_defaultResolution.name].width;
		m_defaultResolution.height = m_resolutionPresets[m_defaultResolution.name].height;

		if (!m_isFullscreen)
			m_isFullscreen = (*defaultOptionsData)["fullscreen"].get<bool>();
		m_defaultFullscreen = m_isFullscreen.value();
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

	file << std::setw(4) << userOptionsJson << std::endl;
}

void options::OptionsManager::resetOptions()
{
	m_currentResolution = m_defaultResolution;
	m_isFullscreen = m_defaultFullscreen;
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

void options::OptionsManager::applyCurrentResolution()
{
	SDL_SetWindowSize(m_window, m_currentResolution.width, m_currentResolution.height);
	SDL_SetWindowFullscreen(m_window, m_isFullscreen ? m_isFullscreen.value() : false);
	centerWindow();
}

void options::OptionsManager::centerWindow()
{
	SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
