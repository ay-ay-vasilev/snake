#include "GameplaySceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

#include "../Game/GameContext.hpp"
#include "../Data/DataManager.hpp"
#include "../Options/OptionsManager.hpp"
#include "../Scenes/Scene.hpp"

void ui::GameplaySceneUI::init()
{
	auto& optionsManager = m_gameContext->getOptionsManager();
	auto& dataManager = m_gameContext->getDataManager();

	const auto resolution = optionsManager->getCurrentResolution();
	const auto windowWidth = resolution.width;
	const auto windowHeight = resolution.height;
	const auto gridWH = dataManager->getConstant<int>("grid_size");
	const auto cellWH = dataManager->getConstant<int>("cell_size");
	const auto gridWidth = gridWH * cellWH;
	const auto gridHeight = gridWH * cellWH;
	m_offset =
		{
			(windowWidth - gridWidth) / 2,
			(windowHeight - gridHeight) / 2
		};
	
	const auto& scoreTextData = dataManager->getConstant<data::TextData>("score_text");
	const auto& gameStateTextData = dataManager->getConstant<data::TextData>("game_state_text");
	const auto& debugTextData = dataManager->getConstant<data::TextData>("debug_text");

	ui::initUIText(scoreTextData, m_scoreText);
	ui::initUIText(gameStateTextData, m_gameStateText);
	ui::initUIText(debugTextData, m_debugText);

	m_scoreText.text = "Score: " + std::to_string(m_score);
	m_gameStateText.text = "START";
	m_debugText.text = "DEBUG";
}

void ui::GameplaySceneUI::handleInput(void* appstate, SDL_Event* event)
{
	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
}

void ui::GameplaySceneUI::update()
{
	m_scoreText.text = "Score: " + std::to_string(m_score);
}

void ui::GameplaySceneUI::render(SDL_Renderer* renderer, int windowFlags)
{
	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window

	ImGui::PushFont(m_fonts["regular_font"]);
	const auto scoreText = m_scoreText.text.c_str();
	ImGui::SetCursorPosX(m_offset.first);
	ImGui::Text("%s", scoreText);

	const auto gameStateText = m_gameStateText.text.c_str();
	ImGui::SetCursorPosX(m_offset.first);
	ImGui::Text("%s", gameStateText);
	ImGui::PopFont();

	ImGui::End();
}

void ui::GameplaySceneUI::addScore(int value)
{
	m_score += value;
}

void ui::GameplaySceneUI::clearScore()
{
	m_score = 0;
}

void ui::GameplaySceneUI::setGameStateText(const std::string_view& text)
{
	m_gameStateText.text = text;
}

void ui::GameplaySceneUI::setDebugText(const std::string_view& text)
{
	m_debugText.text = text;
}

void ui::GameplaySceneUI::getNotified(const ObserverMessage& message)
{
	switch (message.m_type)
	{
	case ObserverMessageType::eAddScore:
		addScore(std::any_cast<int>(message.m_value));
		break;
	case ObserverMessageType::eClearScore:
		clearScore();
		break;
	case ObserverMessageType::eGameState:
		m_gameStateText.text = std::any_cast<std::string>(message.m_value);
		break;
	default:
		break;
	}
}
