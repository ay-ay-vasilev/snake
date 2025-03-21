#include "Constants.hpp"

#include <fstream>
#include <iostream>

namespace constants
{
	void DataManager::LoadConstants()
	{
		const auto fileName = "../data/constants.json";

		std::ifstream file(fileName);
		if (!file.is_open())
		{
			std::cerr << "Game: Failed to open constants file: " << fileName << std::endl;
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

		setFromJson<TextData>(constantsJson, "score_text");
		setFromJson<TextData>(constantsJson, "game_state_text");
		setFromJson<TextData>(constantsJson, "debug_text");
	}
}