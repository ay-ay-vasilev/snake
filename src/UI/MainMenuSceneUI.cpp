#include "MainMenuSceneUI.hpp"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

void ui::MainMenuSceneUI::init()
{
	m_title = "SNAKE";
	m_description = "Press any key to start";
}

void ui::MainMenuSceneUI::handleInput(void* appstate, SDL_Event* event)
{

}

void ui::MainMenuSceneUI::update()
{

}

void ui::MainMenuSceneUI::render(SDL_Renderer* renderer, int windowFlags)
{
	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window
	
	ImGui::PushFont(m_sceneUIData->m_fonts["big_font"]);
	auto titleTextWidth = ImGui::CalcTextSize(m_title.c_str()).x;
	ImGui::SetCursorPosX((m_sceneUIData->m_windowSize.first - titleTextWidth) * 0.5f);
	ImGui::SetCursorPosY(m_sceneUIData->m_windowSize.second * 0.3f);
	ImGui::Text("%s", m_title.c_str());
	ImGui::PopFont();

	ImGui::PushFont(m_sceneUIData->m_fonts["regular_font"]);
	auto descriptionTextWidth = ImGui::CalcTextSize(m_description.c_str()).x;
	ImGui::SetCursorPosX((m_sceneUIData->m_windowSize.first - descriptionTextWidth) * 0.5f);
	ImGui::SetCursorPosY(m_sceneUIData->m_windowSize.second * 0.8f);
	ImGui::Text("%s", m_description.c_str());
	ImGui::PopFont();

	ImGui::End();
}
