#include "GameContext.hpp"

#include <cassert>

context::GameContext::GameContext()
{
	m_dataManager = std::make_unique<data::DataManager>();
	m_optionsManager = std::make_unique<options::OptionsManager>();
	m_dataManager->loadConstants();
	m_optionsManager->loadOptions();
}

std::unique_ptr<data::DataManager>& context::GameContext::getDataManager()
{
	assert(m_dataManager && "DataManager does not exist!");

	return m_dataManager;
}

std::unique_ptr<options::OptionsManager>& context::GameContext::getOptionsManager()
{
	assert(m_optionsManager && "OptionsManager does not exist!");

	return m_optionsManager;
}
