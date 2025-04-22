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
			MainMenuSceneUIButton(
				ImVec2(m_windowSize.first * 0.5f, m_windowSize.second * 0.5f), ImVec2(500, 80),
				std::string("##startBtn"), std::string("Start"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::Gameplay});}
			)
		);
	m_buttons.emplace_back
		(
			MainMenuSceneUIButton(
				ImVec2(m_windowSize.first * 0.5f, m_windowSize.second * 0.6f), ImVec2(500, 80),
				std::string("##optionsBtn"), std::string("Options"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::Options});}
			)
		);
	m_buttons.emplace_back
		(
			MainMenuSceneUIButton(
				ImVec2(m_windowSize.first * 0.5f, m_windowSize.second * 0.7f), ImVec2(500, 80),
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

	ImGui::PushFont(m_fonts["regular_font"]);
	
	ImGui::SetCursorPosY(m_windowSize.second * 0.5f);

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

	if (ImGui::IsKeyDown(ImGuiKey_Enter) || ImGui::IsKeyDown(ImGuiKey_Space) || ImGui::IsKeyDown(ImGuiKey_E))
		m_buttons.at(m_selectedIndex).press();
	if (ImGui::IsKeyReleased(ImGuiKey_Enter) || ImGui::IsKeyReleased(ImGuiKey_Space) || ImGui::IsKeyReleased(ImGuiKey_E))
		m_buttons.at(m_selectedIndex).activate();

	for (auto& button : m_buttons)
		button.renderText();

	ImGui::PopFont();
}
