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

		const int& getWindowWidth() const { return windowWidth_; }
		const int& getWindowHeight() const { return windowHeight_; }

		const int& getFrameStep() const { return frameStep_; }

		const int& getGridSize() const { return gridSize_; }
		const int& getCellSize() const { return cellSize_; }

	private:
		int windowWidth_{};
		int windowHeight_{};
		int gridSize_{};
		int cellSize_{};

		int frameStep_{};

		template <typename T>
		void setValue(const nlohmann::json& data, T& value, const std::string_view& propertyName)
		{
			if (auto it = data.find(propertyName); it != data.end())
				value = it->get<T>();
		}
	};
}