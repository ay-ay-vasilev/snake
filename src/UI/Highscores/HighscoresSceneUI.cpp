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
				ImVec2(0.5f, 0.9f), ImVec2(200, 80), ImVec2(0.5f, 0.5f),
				std::string("##backBtn"), std::string("Back"),
				[this]()
				{
					m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
				}
			)
		);

	m_buttons.front().setIsSelected(true);

	auto& highscoreManager = m_gameContext->getHighscoreManager();
	m_highscores = highscoreManager->getHighscores();
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
	ImGui::Begin("Snake", NULL, static_cast<ImGuiWindowFlags>(windowFlags)); // game screen window

	renderTitle();
	renderHighscoresTable();

	renderButtons();

	ImGui::End();
}

void ui::HighscoresSceneUI::renderTitle()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::PushFont(m_fonts["big_font"]);
	auto titleTextWidth = ImGui::CalcTextSize(m_title.c_str()).x;
	ImGui::SetCursorPosX((resolution.width - titleTextWidth) * 0.5f);
	ImGui::SetCursorPosY(resolution.height * 0.02f);
	ImGui::Text("%s", m_title.c_str());
	ImGui::PopFont();
}

void ui::HighscoresSceneUI::renderHighscoresTable()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::SetCursorPosY(resolution.height * 0.3f);
	static ImGuiTableFlags flags = ImGuiTableFlags_Borders & !ImGuiTableFlags_BordersInnerH & !ImGuiTableFlags_Sortable;

	if (ImGui::BeginTable("table1", 2, flags))
	{
		ImGui::PushFont(m_fonts["regular_font"]);

		ImGui::TableNextRow();

		ImGui::TableSetColumnIndex(0);
		renderCenteredTableText("Name");
		ImGui::TableSetColumnIndex(1);
		renderCenteredTableText("Score");
		ImGui::PopFont();

		ImGui::NewLine();

		ImGui::PushFont(m_fonts["smallish_font"]);
		for (const auto& record : m_highscores)
		{
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			renderCenteredTableText(record.first);
			ImGui::TableSetColumnIndex(1);
			renderCenteredTableText(std::to_string(record.second));
		}
		ImGui::PopFont();
		ImGui::EndTable();
	}
}

void ui::HighscoresSceneUI::renderCenteredTableText(const std::string& text)
{
	int columnWidth = ImGui::GetColumnWidth();
	int textWidth = ImGui::CalcTextSize(text.c_str()).x;
	float offset = (columnWidth - textWidth) * 0.5f;

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
	ImGui::Text("%s", text.c_str());
}
