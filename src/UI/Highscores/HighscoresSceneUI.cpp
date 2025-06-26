#include "HighscoresSceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"

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
				ImVec2(0.1f, 0.9f), ImVec2(200, 80), ImVec2(0.f, 0.5f),
				std::string("##backBtn"), std::string("Back"),
				[this]()
				{
					m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
				}
			)
		);

	m_buttons.front().setIsSelected(true);
}

void ui::HighscoresSceneUI::handleInput(void* appstate, SDL_Event* event)
{
	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
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
	ImGui::SetCursorPosY(resolution.height * 0.02f);
	ImGui::Text("%s", m_title.c_str());
	ImGui::PopFont();

	renderButtons();

	ImGui::End();
}
