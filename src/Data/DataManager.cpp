#include "DataManager.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>

namespace data
{
void DataManager::loadConstants()
{
	std::filesystem::path resDir = RES_DIR;
	const auto fileName = resDir / "data/constants.json";

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "DataManager: Failed to open constants file: " << fileName << std::endl;
		return;
	}

	nlohmann::json constantsJson;
	file >> constantsJson;

	setFromJson<int>(constantsJson, "cell_size");
	setFromJson<int>(constantsJson, "grid_size");
	setFromJson<int>(constantsJson, "nickname_length");
}
}
