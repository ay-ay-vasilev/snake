#pragma once

#include <nlohmann/json.hpp>

namespace data 
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
		DataManager() = default;
		void LoadConstants();

		template <typename T>
		T getConstant(const std::string& key) { return std::any_cast<T>(get(key)); }

	private:
		std::any get(const std::string& key) const
		{
			auto it = m_data.find(key);
			return (it != m_data.end()) ? it->second : std::any();
		}

		template <typename T>
		void set(const std::string& key, const T& value)
		{
			m_data[key] = value;
		}

		template <typename T>
		void setFromJson(const nlohmann::json& data, const std::string& key)
		{
			if (auto it = data.find(key); it != data.end())
				set<T>(key, it->get<T>());
		}

		// Overload instead of specialization
		void setFromJson(const nlohmann::json& data, const std::string& key, TextData*)
		{
			if (auto it = data.find(key); it != data.end())
			{
				TextData newTextData;
				newTextData.x = (*it)["x"].get<int>();
				newTextData.y = (*it)["y"].get<int>();
				newTextData.scale = (*it)["scale"].get<double>();
				set<TextData>(key, newTextData);
			}
		}

		void setFromJson(const nlohmann::json& data, const std::string& key)
		{
			setFromJson(data, key, static_cast<TextData*>(nullptr));
		}

		std::unordered_map<std::string, std::any> m_data;
	};
}
