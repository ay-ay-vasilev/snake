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
	renderButtons();

	ImGui::End();
}

void ui::SaveHighscoreSceneUI::renderTitle()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::PushFont(m_fonts["regular_font"]);
	const std::string titleStr = "Enter your name:";
	auto titleTextWidth = ImGui::CalcTextSize(titleStr.c_str()).x;
	auto titleTextHeight = ImGui::CalcTextSize(titleStr.c_str()).y;
	ImVec2 textPos = ImVec2(
		(resolution.width - titleTextWidth) * 0.5f,
		(resolution.height - titleTextHeight) * 0.2f
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
