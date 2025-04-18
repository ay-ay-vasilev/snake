#include "MainMenuSceneUI.hpp"

#include "../Scenes/Scene.hpp"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

void ui::MainMenuSceneUI::init()
{
	m_title = "SNAKE";
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
	ImGui::SetCursorPosY(m_sceneUIData->m_windowSize.second * 0.2f);
	ImGui::Text("%s", m_title.c_str());
	ImGui::PopFont();

	ImGui::PushFont(m_sceneUIData->m_fonts["regular_font"]);
	
	ImGui::SetCursorPosY(m_sceneUIData->m_windowSize.second * 0.5f);

	renderButton("##startBtn", "Start", [this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::eGameplay});});
	renderButton("##optionsBtn", "Options");
	renderButton("##exitBtn", "Exit", [this](){ m_commandCallback({eUICommandType::QuitGame, std::nullopt});});

	ImGui::PopFont();

	ImGui::End();
}

void ui::MainMenuSceneUI::renderButton(std::string buttonId, std::string label, std::function<void()> callback)
{
	ImVec2 buttonSize = ImVec2(500, 80);
	ImGui::SetCursorPosX((m_sceneUIData->m_windowSize.first - buttonSize.x) * 0.5f);
	if (ImGui::InvisibleButton(buttonId.c_str(), buttonSize))
	{
		if (callback) callback();
	}
	ImVec2 pos = ImGui::GetItemRectMin();
	ImU32 color = IM_COL32(255, 255, 255, 255);
	if (ImGui::IsItemHovered() && !ImGui::IsItemActive())
		color = IM_COL32(255, 180, 0, 255);
	else if (ImGui::IsItemActive())
		color = IM_COL32(255, 100, 0, 255);
	ImVec2 textSize = ImGui::CalcTextSize(label.c_str());
	ImVec2 textPos = ImVec2(
		pos.x + (buttonSize.x - textSize.x) * 0.5f,
		pos.y + (buttonSize.y - textSize.y) * 0.5f
	);
	ImGui::GetWindowDrawList()->AddText(textPos, color, label.c_str());
}
