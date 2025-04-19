#include "MainMenuSceneUI.hpp"

#include "../../Scenes/Scene.hpp"
#include "../../Constants/Constants.hpp"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

void ui::MainMenuSceneUI::init()
{
	m_title = "SNAKE";

	auto& dataManager = constants::DataManager::getInstance();

	const auto windowWidth = dataManager.getConstant<int>("window_width");
	const auto windowHeight = dataManager.getConstant<int>("window_height");

	m_buttons.emplace_back
		(
			MainMenuSceneUIButton(
				ImVec2(windowWidth * 0.5f, windowHeight * 0.5f), ImVec2(500, 80),
				std::string("##startBtn"), std::string("Start"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::eGameplay});}
			)
		);
	m_buttons.emplace_back
		(
			MainMenuSceneUIButton(
				ImVec2(windowWidth * 0.5f, windowHeight * 0.6f), ImVec2(500, 80),
				std::string("##optionsBtn"), std::string("Options"),
				[](){}
			)
		);
	m_buttons.emplace_back
		(
			MainMenuSceneUIButton(
				ImVec2(windowWidth * 0.5f, windowHeight * 0.7f), ImVec2(500, 80),
				std::string("##exitBtn"), std::string("Exit"),
				[this](){m_commandCallback({eUICommandType::QuitGame, std::nullopt});}
			)
		);

	m_buttons.front().setIsSelected(true);
	m_selectedIndex = 0;
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

	renderButtons();

	ImGui::End();
}

void ui::MainMenuSceneUI::renderButtons()
{
	if (m_buttons.empty())
		return;

	if (ImGui::IsKeyPressed(ImGuiKey_S) || ImGui::IsKeyPressed(ImGuiKey_DownArrow))
		m_selectedIndex = (m_selectedIndex + 1) % m_buttons.size();

	if (ImGui::IsKeyPressed(ImGuiKey_W) || ImGui::IsKeyPressed(ImGuiKey_UpArrow))
		m_selectedIndex = (m_selectedIndex - 1 + m_buttons.size()) % m_buttons.size();

	for (auto& button : m_buttons)
	{
		button.setIsSelected(false);
	}
		m_buttons.at(m_selectedIndex).setIsSelected(true);

	ImGui::PushFont(m_sceneUIData->m_fonts["regular_font"]);
	
	ImGui::SetCursorPosY(m_sceneUIData->m_windowSize.second * 0.5f);

	for (auto& button : m_buttons)
		button.renderButton();

	bool hoveredExists = false;
	int i = 0;
	for (auto& button : m_buttons)
	{
		if (button.isHovered())
		{
			hoveredExists = true;
			m_selectedIndex = i;
			break;
		}
		i++;
	}

	if (hoveredExists)
	{
		for (auto& button : m_buttons)
		{
			if (button.isHovered())
				continue;
			button.setIsSelected(false);
		}
	}

	if (ImGui::IsKeyDown(ImGuiKey_Enter) || ImGui::IsKeyDown(ImGuiKey_Space))
		m_buttons.at(m_selectedIndex).press();
	if (ImGui::IsKeyReleased(ImGuiKey_Enter) || ImGui::IsKeyReleased(ImGuiKey_Space))
		m_buttons.at(m_selectedIndex).activate();

	for (auto& button : m_buttons)
		button.renderText();

	ImGui::PopFont();
}
