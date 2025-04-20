#include "OptionsSceneUI.hpp"

#include "imgui.h"
#include <SDL3_image/SDL_image.h>

#include "../UICommand.hpp"
#include "../../Scenes/Scene.hpp"

void ui::OptionsSceneUI::init()
{

}

void ui::OptionsSceneUI::handleInput(void* appstate, SDL_Event* event)
{
	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
}

void ui::OptionsSceneUI::update()
{

}

void ui::OptionsSceneUI::render(SDL_Renderer* renderer, int windowFlags)
{
	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window
	const std::string sceneTitle = "Options";
	
	ImGui::PushFont(m_sceneUIData->m_fonts["big_font"]);
	auto titleTextWidth = ImGui::CalcTextSize(sceneTitle.c_str()).x;
	ImGui::SetCursorPosX((m_sceneUIData->m_windowSize.first - titleTextWidth) * 0.5f);
	ImGui::SetCursorPosY(m_sceneUIData->m_windowSize.second * 0.2f);
	ImGui::Text("%s", sceneTitle.c_str());
	ImGui::PopFont();

	ImGui::End();
}
