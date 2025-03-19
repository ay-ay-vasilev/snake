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
		
		setValue<int>(constantsJson, windowWidth, "window_width");
		setValue<int>(constantsJson, windowHeight, "window_height");
		setValue<int>(constantsJson, frameStep, "frame_step");
		setValue<int>(constantsJson, cellSize, "cell_size");
		setValue<int>(constantsJson, gridSize, "grid_size");
	}
}