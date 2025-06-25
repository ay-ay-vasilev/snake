#include "HighscoresSceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"
#include "Version.hpp"

#include "../../Scenes/Scene.hpp"
#include "../../Game/GameContext.hpp"

void ui::HighscoresSceneUI::init()
{
	m_title = "Highscores";

	auto& optionsManager = m_gameContext->getOptionsManager();

	const auto resolution = optionsManager->getCurrentResolution();

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
				std::string("##exitBtn"), std::string("Exit"),
				[this](){m_commandCallback({eUICommandType::QuitGame, std::nullopt});}
			)
		);

	m_buttons.front().setIsSelected(true);
}

void ui::HighscoresSceneUI::handleInput(void* appstate, SDL_Event* event)
{
	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		m_commandCallback({eUICommandType::QuitGame, std::nullopt});
}

void ui::HighscoresSceneUI::update()
{

}

void ui::HighscoresSceneUI::render(SDL_Renderer* renderer, int windowFlags)
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window
	
	ImGui::PushFont(m_fonts["big_font"]);
	auto titleTextWidth = ImGui::CalcTextSize(m_title.c_str()).x;
	ImGui::SetCursorPosX((resolution.width - titleTextWidth) * 0.5f);
	ImGui::SetCursorPosY(resolution.height * 0.2f);
	ImGui::Text("%s", m_title.c_str());
	ImGui::PopFont();

	renderButtons();

	ImGui::End();
}
