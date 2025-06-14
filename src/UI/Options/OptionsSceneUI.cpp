#include "OptionsSceneUI.hpp"

#include "imgui.h"
#include <SDL3_image/SDL_image.h>

#include "../UICommand.hpp"
#include "../../Scenes/Scene.hpp"
#include "../../Game/GameContext.hpp"

void ui::OptionsSceneUI::init()
{
	auto& optionsManager = m_gameContext->getOptionsManager();

	m_resolutions = optionsManager->getResolutionPresets();
	m_selectedResolutionName = optionsManager->getCurrentResolution().name;

	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.1f, 0.9f), ImVec2(200, 80), ImVec2(0.f, 0.5f),
				std::string("##backBtn"), std::string("Back"),
				[this]()
				{
					m_closeResolutionTree = true;
					m_commandCallback({eUICommandType::ChangeScene, scene::eSceneType::MainMenu});
				}
			)
		);
	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.5f, 0.9f), ImVec2(200, 80), ImVec2(0.5f, 0.5f),
				std::string("##resetBtn"), std::string("Reset"),
				[this]()
				{
					auto& optionsManager = m_gameContext->getOptionsManager();
					optionsManager->resetOptions();
					optionsManager->saveOptions();
					optionsManager->applyCurrentResolution();
					m_selectedResolutionName = optionsManager->getCurrentResolution().name;
					m_closeResolutionTree = true;
				}
			)
		);
	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.9f, 0.9f), ImVec2(200, 80), ImVec2(1.f, 0.5f),
				std::string("##saveBtn"), std::string("Save"),
				[this]()
				{
					auto& optionsManager = m_gameContext->getOptionsManager();
					const auto& currentResolution = m_resolutions.at(m_selectedResolutionName);
					optionsManager->setCurrentResolution(currentResolution);
					optionsManager->applyCurrentResolution();
					optionsManager->saveOptions();
					m_closeResolutionTree = true;
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

	renderTitle();

	renderResolutionsOption();

	renderButtons();

	ImGui::End();
}

void ui::OptionsSceneUI::renderTitle()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();
	const std::string sceneTitle = "Options";

	ImGui::PushFont(m_fonts["big_font"]);
	auto titleTextWidth = ImGui::CalcTextSize(sceneTitle.c_str()).x;
	ImGui::SetCursorPosX((resolution.width- titleTextWidth) * 0.5f);
	ImGui::SetCursorPosY(resolution.height * 0.1f);
	ImGui::Text("%s", sceneTitle.c_str());
	ImGui::PopFont();
}

void ui::OptionsSceneUI::renderResolutionsOption()
{
	const auto& window = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));

	ImGui::SetCursorPosX(window.width * 0.1f);
	ImGui::PushFont(m_fonts["regular_font"]);
	ImGui::Text("Resolution:");
	ImGui::SameLine(window.width * 0.7f);
	renderResolutionsTreeNode();
	ImGui::PopFont();
	ImGui::PopStyleColor(3);
}

void ui::OptionsSceneUI::renderResolutionsTreeNode()
{
	const auto& window = m_gameContext->getOptionsManager()->getCurrentResolution();

	if (m_closeResolutionTree)
	{
		ImGui::SetNextItemOpen(false, ImGuiCond_Always);
		m_closeResolutionTree = false;
	}

	if (ImGui::TreeNode(m_selectedResolutionName.c_str()))
	{
		ImGui::Indent(window.width * 0.7f);
		ImGui::Indent();
		int index = 0;
		for (const auto resolution : m_resolutions)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 0));
			if (ImGui::Selectable(resolution.first.c_str(), resolution.first == m_selectedResolutionName))
			{
				m_selectedResolutionName = resolution.first;
				m_closeResolutionTree = true;
			}
			ImGui::PopStyleColor(1);

			ImVec2 itemMin = ImGui::GetItemRectMin();
			ImVec2 itemMax = ImGui::GetItemRectMax();
			ImVec2 textPos = ImVec2(itemMin.x, itemMin.y + ImGui::GetStyle().FramePadding.y);

			ImU32 textColor = IM_COL32(255, 255, 255, 255); // Default
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
				textColor = IM_COL32(255, 165, 0, 255); // Orange
			else if (resolution.first == m_selectedResolutionName)
				textColor = IM_COL32(255, 255, 0, 255); // Yellow

			ImGui::GetWindowDrawList()->AddText(textPos, textColor, resolution.first.c_str());
			++index;
		}
		ImGui::Unindent();
		ImGui::Unindent();
		ImGui::TreePop();
	}
}
