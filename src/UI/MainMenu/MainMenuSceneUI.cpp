#include "MainMenuSceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"
#include "Version.hpp"

#include "../../Scenes/Scene.hpp"
#include "../../Game/GameContext.hpp"

void ui::MainMenuSceneUI::init()
{
	m_title = "SNAKE";
	m_version = "v" + std::string(PROJECT_VERSION);

	const auto& optionsManager = m_gameContext->getOptionsManager();

	const auto& resolution = optionsManager->getCurrentResolution();

	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.5f, 0.5f), ImVec2(500, 80), ImVec2(0.5f, 0.5f),
				std::string("##startBtn"), std::string("Start"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::Gameplay});}
			)
		);
	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.5f, 0.6f), ImVec2(500, 80), ImVec2(0.5f, 0.5f),
				std::string("##optionsBtn"), std::string("Options"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::Options});}
			)
		);
	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.5f, 0.7f), ImVec2(500, 80), ImVec2(0.5f, 0.5f),
				std::string("##highscoresBtn"), std::string("Highscores"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::Highscores});}
			)
		);
	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.5f, 0.8f), ImVec2(500, 80), ImVec2(0.5f, 0.5f),
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
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window
	
	ImGui::PushFont(m_fonts["big_font"]);
	const auto& titleTextWidth = ImGui::CalcTextSize(m_title.c_str()).x;
	ImGui::SetCursorPosX((resolution.width - titleTextWidth) * 0.5f);
	ImGui::SetCursorPosY(resolution.height * 0.2f);
	ImGui::Text("%s", m_title.c_str());
	ImGui::PopFont();

	renderVersion();
	renderButtons();

	ImGui::End();
}

void ui::MainMenuSceneUI::renderVersion()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();
	
	ImGui::PushFont(m_fonts["small_font"]);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(140, 140, 140, 255));
	const auto& titleTextSize = ImGui::CalcTextSize(m_version.c_str());
	ImGui::SetCursorPosX(0);
	ImGui::SetCursorPosY(resolution.height - titleTextSize.y);
	ImGui::Text("%s", m_version.c_str());
	ImGui::PopStyleColor();
	ImGui::PopFont();
}
