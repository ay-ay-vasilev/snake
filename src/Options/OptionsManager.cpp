#include "OptionsManager.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

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
			m_resolutionPresets.emplace_back(resolution);
		}
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
		for (const auto& resolution : m_resolutionPresets)
		{
			if (resolution.name != resolutionName)
				continue;

			m_currentResolution = resolution;
			break;
		}
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

	file << std::setw(4) << userOptionsJson << std::endl;
}

options::Resolution options::OptionsManager::getCurrentResolution() const
{
	return m_currentResolution;
}

std::vector<options::Resolution> options::OptionsManager::getResolutionPresets() const
{
	return m_resolutionPresets;
}

void options::OptionsManager::setCurrentResolution(options::Resolution newResolution)
{
	m_currentResolution = newResolution;
}
