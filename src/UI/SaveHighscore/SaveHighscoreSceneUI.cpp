#include "SaveHighscoreSceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"

#include "../../Scenes/Scene.hpp"
#include "../../Game/GameContext.hpp"
#include "../../Highscores/HighscoreManager.hpp"

void ui::SaveHighscoreSceneUI::init()
{
	auto& optionsManager = m_gameContext->getOptionsManager();

	const auto resolution = optionsManager->getCurrentResolution();

	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.5f, 0.8f), ImVec2(500, 80), ImVec2(0.5f, 0.5f),
				std::string("##confirmBtn"), std::string("Confirm"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});}
			)
		);

	m_buttons.front().setIsSelected(true);
	m_selectionBusy = true;
	m_playerName = "";
	m_isWindowAppearing = true;
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
	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window

	renderTitle();
	renderScore();
	renderPlayerNameInput();
	renderButtons();

	ImGui::End();
}

void ui::SaveHighscoreSceneUI::renderPlayerNameInput()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();
	char buf[7] = {};
	snprintf(buf, sizeof(buf), "%s", m_playerName.c_str());

	if (m_isWindowAppearing)
	{
		ImGui::SetKeyboardFocusHere();
		m_isWindowAppearing = false;
	}

	ImGui::PushFont(m_fonts["big_font"]);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	const std::string testName = "WWWWWW";
	const auto textWidth = ImGui::CalcTextSize(testName.c_str()).x * 1.1f;
	const auto textHeight = ImGui::CalcTextSize(testName.c_str()).y;
	ImGui::SetNextItemWidth(textWidth);
	ImVec2 inputPos = ImVec2(
		(resolution.width - ImGui::CalcTextSize(buf).x) * 0.5f,
		(resolution.height - textHeight) * 0.3f
	);
	ImGui::SetCursorPosX(inputPos.x);
	ImGui::SetCursorPosY(inputPos.y);
	ImGui::InputText("##playerNameInput", buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank);
	ImGui::PopStyleColor(2);
	ImGui::PopFont();

	m_playerName.assign(buf);
}

void ui::SaveHighscoreSceneUI::renderTitle()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::PushFont(m_fonts["regular_font"]);
	const std::string titleStr = "Enter your name:";
	const auto titleTextWidth = ImGui::CalcTextSize(titleStr.c_str()).x;
	const auto titleTextHeight = ImGui::CalcTextSize(titleStr.c_str()).y;
	ImVec2 textPos = ImVec2(
		(resolution.width - titleTextWidth) * 0.5f,
		(resolution.height - titleTextHeight) * 0.15f
	);
	ImGui::SetCursorPosX(textPos.x);
	ImGui::SetCursorPosY(textPos.y);
	ImGui::Text("%s", titleStr.c_str());
	ImGui::PopFont();
}

void ui::SaveHighscoreSceneUI::renderScore()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();
	const auto& highscoreManager = m_gameContext->getHighscoreManager();

	ImGui::PushFont(m_fonts["regular_font"]);
	const std::string scoreStr = "Your score: " + std::to_string(highscoreManager->getCurrentScore());
	auto scoreStrWidth = ImGui::CalcTextSize(scoreStr.c_str()).x;
	auto scoreStrHeight = ImGui::CalcTextSize(scoreStr.c_str()).y;
	ImVec2 textPos = ImVec2(
		(resolution.width - scoreStrWidth) * 0.5f,
		(resolution.height - scoreStrHeight) * 0.5f
	);
	ImGui::SetCursorPosX(textPos.x);
	ImGui::SetCursorPosY(textPos.y);
	ImGui::Text("%s", scoreStr.c_str());
	ImGui::PopFont();
}
