#include "GameplaySceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

#include "../../Game/GameContext.hpp"
#include "../../Scenes/Scene.hpp"

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
	
	m_scoreText= "Score: " + std::to_string(m_score);
	m_isLose = false;
	m_isNewScore = false;
	m_isPaused = false;
}

void ui::GameplaySceneUI::handleInput(void* appstate, SDL_Event* event)
{
	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
}

void ui::GameplaySceneUI::update()
{
	m_scoreText = "Score: " + std::to_string(m_score);
}

void ui::GameplaySceneUI::render(SDL_Renderer* renderer, int windowFlags)
{
	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window

	ImGui::PushFont(m_fonts["regular_font"]);
	ImGui::SetCursorPosX(m_offset.first);
	ImGui::Text("%s", m_scoreText.c_str());
	ImGui::PopFont();

	if (m_isPaused)
	{
		renderPause();
	}
	if (m_isLose)
	{
		renderLose();
	}
	if (m_isNewScore)
	{
		renderNewScore();
	}

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

void ui::GameplaySceneUI::renderPause()
{
	const auto resolution = m_gameContext->getOptionsManager()->getCurrentResolution();
	ImDrawList* draw_list = ImGui::GetForegroundDrawList();

	draw_list->AddRectFilled(
		ImVec2(0, 0),
		{ static_cast<float>(resolution.width), static_cast<float>(resolution.height) },
		IM_COL32(0, 0, 0, 128)
	);

	ImGui::PushFont(m_fonts["big_font"]);
	const std::string titleStr = "PAUSE";
	auto titleTextWidth = ImGui::CalcTextSize(titleStr.c_str()).x;
	auto titleTextHeight = ImGui::CalcTextSize(titleStr.c_str()).y;
	ImVec2 textPos = ImVec2(
		(resolution.width - titleTextWidth) * 0.5f,
		(resolution.height - titleTextHeight) * 0.5f
	);
	draw_list->AddText(textPos, IM_COL32(255, 255, 255, 255), titleStr.c_str());
	ImGui::PopFont();
}

void ui::GameplaySceneUI::renderLose()
{
	const auto resolution = m_gameContext->getOptionsManager()->getCurrentResolution();
	ImDrawList* draw_list = ImGui::GetForegroundDrawList();

	draw_list->AddRectFilled(
		ImVec2(0, 0),
		{ static_cast<float>(resolution.width), static_cast<float>(resolution.height) },
		IM_COL32(0, 0, 0, 128)
	);

	ImGui::PushFont(m_fonts["big_font"]);
	const std::string titleStr = "You died!";
	auto titleTextWidth = ImGui::CalcTextSize(titleStr.c_str()).x;
	auto titleTextHeight = ImGui::CalcTextSize(titleStr.c_str()).y;
	ImVec2 textPos = ImVec2(
		(resolution.width - titleTextWidth) * 0.5f,
		(resolution.height - titleTextHeight) * 0.5f
	);
	draw_list->AddText(textPos, IM_COL32(255, 255, 255, 255), titleStr.c_str());
	ImGui::PopFont();
}

void ui::GameplaySceneUI::renderNewScore()
{
	const auto resolution = m_gameContext->getOptionsManager()->getCurrentResolution();
	ImDrawList* draw_list = ImGui::GetForegroundDrawList();

	draw_list->AddRectFilled(
		ImVec2(0, 0),
		{ static_cast<float>(resolution.width), static_cast<float>(resolution.height) },
		IM_COL32(0, 0, 0, 128)
	);

	ImGui::PushFont(m_fonts["big_font"]);
	const std::string titleStr = "New score!";
	auto titleTextWidth = ImGui::CalcTextSize(titleStr.c_str()).x;
	auto titleTextHeight = ImGui::CalcTextSize(titleStr.c_str()).y;
	ImVec2 textPos = ImVec2(
		(resolution.width - titleTextWidth) * 0.5f,
		(resolution.height - titleTextHeight) * 0.5f
	);
	draw_list->AddText(textPos, IM_COL32(255, 255, 255, 255), titleStr.c_str());
	ImGui::PopFont();
}

void ui::GameplaySceneUI::getNotified(const ObserverMessage& message)
{
	std::string messageStr;
	switch (message.m_type)
	{
	case ObserverMessageType::eAddScore:
		addScore(std::any_cast<int>(message.m_value));
		break;
	case ObserverMessageType::eClearScore:
		clearScore();
		break;
	case ObserverMessageType::eGameState:
		messageStr = std::any_cast<std::string>(message.m_value);
		if (messageStr == "PAUSED")
		{
			m_isPaused = true;
		}
		else if (messageStr == "LOSE")
		{
			const auto& highscoreManager = m_gameContext->getHighscoreManager();
			highscoreManager->setCurrentScore(m_score);

			if (highscoreManager->isNewHighscore())
				m_isNewScore = true;
			else
				m_isLose = true;
		}
		else
		{
			m_isLose = false;
			m_isPaused = false;
		}
		break;
	case ObserverMessageType::eChangeScene:
		messageStr = std::any_cast<std::string>(message.m_value);
		if (messageStr == "SaveHighscore")
		{
			if (m_isNewScore)
				m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::SaveHighscore});
			else if (m_isLose)
				m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
			m_isLose = false;
			m_isNewScore = false;
			m_isPaused = false;
		}
		break;
	default:
		break;
	}
}
