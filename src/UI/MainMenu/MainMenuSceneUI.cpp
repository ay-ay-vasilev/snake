#include "MainMenuSceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"
#include "Version.hpp"

#include "../../Scenes/Scene.hpp"
#include "../../Game/GameContext.hpp"
#include "../../Data/DataManager.hpp"

void ui::MainMenuSceneUI::init()
{
	m_title = "SNAKE";
	m_version = "v" + std::string(PROJECT_VERSION);

	auto& dataManager = m_gameContext->getDataManager();

	m_windowSize.first = dataManager->getConstant<int>("window_width");
	m_windowSize.second = dataManager->getConstant<int>("window_height");

	m_buttons.emplace_back
		(
			UIButton(
				ImVec2(m_windowSize.first * 0.5f, m_windowSize.second * 0.5f), ImVec2(500, 80), ImVec2(0.5f, 0.5f),
				std::string("##startBtn"), std::string("Start"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::Gameplay});}
			)
		);
	m_buttons.emplace_back
		(
			UIButton(
				ImVec2(m_windowSize.first * 0.5f, m_windowSize.second * 0.6f), ImVec2(500, 80), ImVec2(0.5f, 0.5f),
				std::string("##optionsBtn"), std::string("Options"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::Options});}
			)
		);
	m_buttons.emplace_back
		(
			UIButton(
				ImVec2(m_windowSize.first * 0.5f, m_windowSize.second * 0.7f), ImVec2(500, 80), ImVec2(0.5f, 0.5f),
				std::string("##exitBtn"), std::string("Exit"),
				[this](){m_commandCallback({eUICommandType::QuitGame, std::nullopt});}
			)
		);

	m_buttons.front().setIsSelected(true);
}

void ui::MainMenuSceneUI::handleInput(void* appstate, SDL_Event* event)
{
	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		m_commandCallback({eUICommandType::QuitGame, std::nullopt});
}

void ui::MainMenuSceneUI::update()
{

}

void ui::MainMenuSceneUI::render(SDL_Renderer* renderer, int windowFlags)
{
	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window
	
	ImGui::PushFont(m_fonts["big_font"]);
	auto titleTextWidth = ImGui::CalcTextSize(m_title.c_str()).x;
	ImGui::SetCursorPosX((m_windowSize.first - titleTextWidth) * 0.5f);
	ImGui::SetCursorPosY(m_windowSize.second * 0.2f);
	ImGui::Text("%s", m_title.c_str());
	ImGui::PopFont();

	renderVersion();
	renderButtons();

	ImGui::End();
}

void ui::MainMenuSceneUI::renderVersion()
{
	ImGui::PushFont(m_fonts["small_font"]);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(140, 140, 140, 255));
	auto titleTextSize = ImGui::CalcTextSize(m_version.c_str());
	ImGui::SetCursorPosX(0);
	ImGui::SetCursorPosY(m_windowSize.second - titleTextSize.y);
	ImGui::Text("%s", m_version.c_str());
	ImGui::PopStyleColor();
	ImGui::PopFont();
}
