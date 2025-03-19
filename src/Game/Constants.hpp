#pragma once

#include <nlohmann/json.hpp>

namespace constants
{
	constexpr int TEXT_SCORE_SCALE = 2;
	constexpr int TEXT_SCORE_X = 0;
	constexpr int TEXT_SCORE_Y = -30;

	constexpr int TEXT_DIRECTION_SCALE = 2;
	constexpr int TEXT_DIRECTION_X = 0;
	constexpr int TEXT_DIRECTION_Y = -60;

	class DataManager
	{
	public:

		static DataManager& getInstance()
		{
			static DataManager dataManager;
			return dataManager;
		}

		void LoadConstants();

		const int& getWindowWidth() const { return windowWidth; }
		const int& getWindowHeight() const { return windowHeight; }

		const int& getFrameStep() const { return frameStep; }

		const int& getGridSize() const { return gridSize; }
		const int& getCellSize() const { return cellSize; }

	private:
		int windowWidth{};
		int windowHeight{};
		int gridSize{};
		int cellSize{};

		int frameStep{};

		template <typename T>
		void setValue(const nlohmann::json& data, T& value, const std::string_view& propertyName)
		{
			if (auto it = data.find(propertyName); it != data.end())
				value = it->get<T>();
		}
	};
}