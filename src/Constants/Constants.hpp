#pragma once

#include <nlohmann/json.hpp>

namespace constants
{
	struct TextData
	{
		int scale;
		int x;
		int y;
	};

	class DataManager
	{
	public:

		static DataManager& getInstance()
		{
			static DataManager dataManager;
			return dataManager;
		}

		void LoadConstants();

		template <typename T>
		T getConstant(const std::string& key) { return std::any_cast<T>(get(key)); }

	private:
		std::unordered_map<std::string, std::any> data_;

		std::any get(const std::string& key) const
		{
			auto it = data_.find(key);
			return (it != data_.end()) ? it->second : std::any();
		}

		template <typename T>
		void set(const std::string& key, const T& value)
		{
			data_[key] = value;
		}

		template <typename T>
		void setFromJson(const nlohmann::json& data, const std::string& key)
		{
			if (auto it = data.find(key); it != data.end())
				set<T>(key, it->get<T>());
		}

		template <>
		void setFromJson<TextData>(const nlohmann::json& data, const std::string& key)
		{
			if (auto it = data.find(key); it != data.end())
			{
				TextData newTextData;
				newTextData.x = data[key]["x"].get<int>();
				newTextData.y = data[key]["y"].get<int>();
				newTextData.scale = data[key]["scale"].get<double>();
				set<TextData>(key, newTextData);
			}
		}
	};
}