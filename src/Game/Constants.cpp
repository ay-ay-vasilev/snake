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
		
		setValue<int>(constantsJson, windowWidth_, "window_width");
		setValue<int>(constantsJson, windowHeight_, "window_height");
		setValue<int>(constantsJson, frameStep_, "frame_step");
		setValue<int>(constantsJson, cellSize_, "cell_size");
		setValue<int>(constantsJson, gridSize_, "grid_size");
	}
}