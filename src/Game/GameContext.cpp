#include "GameContext.hpp"

#include <cassert>

#include "../Data/DataManager.hpp"

context::GameContext::GameContext()
{
	m_dataManager = std::make_unique<data::DataManager>();
	m_dataManager->LoadConstants();
}

std::unique_ptr<data::DataManager>& context::GameContext::getDataManager()
{
	assert(m_dataManager && "DataManager does not exist!");

	return m_dataManager;
}
