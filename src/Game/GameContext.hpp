#pragma once

#include <memory>

namespace data
{
	class DataManager;
}

namespace context
{
class GameContext
{
public:
	GameContext();
	std::unique_ptr<data::DataManager>& getDataManager();

private:
	std::unique_ptr<data::DataManager> m_dataManager{};
};
}
