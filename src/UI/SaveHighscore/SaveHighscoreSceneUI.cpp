#include "SaveHighscoreSceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"

#include "../../Scenes/Scene.hpp"
#include "../../Game/GameContext.hpp"

void ui::SaveHighscoreSceneUI::init()
{
	auto& optionsManager = m_gameContext->getOptionsManager();

	const auto resolution = optionsManager->getCurrentResolution();

	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.5f, 0.8f), ImVec2(500, 80), ImVec2(0.5f, 0.5f),
				std::string("##exitBtn"), std::string("Exit"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});}
			)
		);

	m_buttons.front().setIsSelected(true);
}

void ui::SaveHighscoreSceneUI::handleInput(void* appstate, SDL_Event* event)
{
	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
}

void ui::SaveHighscoreSceneUI::update()
{

}

void ui::SaveHighscoreSceneUI::render(SDL_Renderer* renderer, int windowFlags)
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window

	renderButtons();

	ImGui::End();
}
