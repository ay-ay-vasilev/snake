#include "OptionsSceneUI.hpp"

#include "imgui.h"
#include <SDL3_image/SDL_image.h>

#include "../UICommand.hpp"
#include "../../Scenes/Scene.hpp"
#include "../../Game/GameContext.hpp"
#include "../../Data/DataManager.hpp"


void ui::OptionsSceneUI::init()
{
	auto& dataManager = m_gameContext->getDataManager();

	m_windowSize.first = dataManager->getConstant<int>("window_width");
	m_windowSize.second = dataManager->getConstant<int>("window_height");

	auto& optionsManager = m_gameContext->getOptionsManager();

	m_resolutions = optionsManager->getResolutionPresets();
	const auto selectedResolution = optionsManager->getCurrentResolution();
	int index = 0;
	for (const auto& resolution : m_resolutions)
	{
		if (resolution.name != selectedResolution.name)
		{
			++index;
			continue;
		}
		m_selectedResolutionId = index;
		break;
	}

	m_buttons.emplace_back
		(
			UIButton(
				ImVec2(m_windowSize.first * 0.1f, m_windowSize.second * 0.9f), ImVec2(200, 80), ImVec2(0.f, 0.5f),
				std::string("##cancelBtn"), std::string("Cancel"),
				[this](){m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});}
			)
		);
	m_buttons.emplace_back
		(
			UIButton(
				ImVec2(m_windowSize.first * 0.5f, m_windowSize.second * 0.9f), ImVec2(200, 80), ImVec2(0.5f, 0.5f),
				std::string("##resetBtn"), std::string("Reset"),
				[this](){}
			)
		);
	m_buttons.emplace_back
		(
			UIButton(
				ImVec2(m_windowSize.first * 0.9f, m_windowSize.second * 0.9f), ImVec2(200, 80), ImVec2(1.f, 0.5f),
				std::string("##saveBtn"), std::string("Save"),
				[this]()
				{
					auto& optionsManager = m_gameContext->getOptionsManager();
					optionsManager->setCurrentResolution(m_resolutions.at(m_selectedResolutionId));
					optionsManager->saveOptions();
					m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
				}
			)
		);

	m_buttons.back().setIsSelected(true);
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
	
	ImGui::PushFont(m_fonts["big_font"]);
	auto titleTextWidth = ImGui::CalcTextSize(sceneTitle.c_str()).x;
	ImGui::SetCursorPosX((m_windowSize.first - titleTextWidth) * 0.5f);
	ImGui::SetCursorPosY(m_windowSize.second * 0.1f);
	ImGui::Text("%s", sceneTitle.c_str());
	ImGui::PopFont();

	ImGui::PushFont(m_fonts["regular_font"]);
	ImGui::Text("Resolution:");
	ImGui::SameLine(800);
	if (ImGui::TreeNode(m_resolutions.at(m_selectedResolutionId).name.c_str()))
	{
		ImGui::Indent(800);
		ImGui::Indent();
		int index = 0;
		for (const auto resolution : m_resolutions)
		{
			if (ImGui::Selectable(resolution.name.c_str(), m_selectedResolutionId == index))
			{
				m_selectedResolutionId = index;
			}
			++index;
		}
		ImGui::Unindent();
		ImGui::Unindent();
		ImGui::TreePop();
	}
	ImGui::PopFont();

	renderButtons();

	ImGui::End();
}

