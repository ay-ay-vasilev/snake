#include "DataManager.hpp"

#include <fstream>
#include <iostream>

namespace data
{
void DataManager::loadConstants()
{
	const auto fileName = "../res/data/constants.json";

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "DataManager: Failed to open constants file: " << fileName << std::endl;
		return;
	}

	nlohmann::json constantsJson;
	file >> constantsJson;

	setFromJson<int>(constantsJson, "window_width");
	setFromJson<int>(constantsJson, "window_height");
	setFromJson<int>(constantsJson, "frame_step");
	setFromJson<int>(constantsJson, "cell_size");
	setFromJson<int>(constantsJson, "grid_size");

	setFromJson<int>(constantsJson, "grid_size");
	setFromJson<int>(constantsJson, "grid_size");

	setFromJson(constantsJson, "score_text");
	setFromJson(constantsJson, "game_state_text");
	setFromJson(constantsJson, "debug_text");
}
}
