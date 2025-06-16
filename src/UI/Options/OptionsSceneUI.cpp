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
	m_isFullscreen = optionsManager->getIsFullscreen();

	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.1f, 0.9f), ImVec2(200, 80), ImVec2(0.f, 0.5f),
				std::string("##backBtn"), std::string("Back"),
				[this]()
				{
					m_shouldResolutionTreeClose = true;
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
					m_isFullscreen = optionsManager->getIsFullscreen();
					m_shouldResolutionTreeClose = true;
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
					optionsManager->setIsFullscreen(m_isFullscreen);
					optionsManager->applyCurrentResolution();
					optionsManager->saveOptions();
					m_shouldResolutionTreeClose = true;
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
	
	ImGui::GetWindowDrawList()->ChannelsSplit(2);
	ImGui::GetWindowDrawList()->ChannelsSetCurrent(1);

	renderTitle();
	renderResolutionsOption();
	renderFullscreenOption();

	ImGui::GetWindowDrawList()->ChannelsSetCurrent(0);
	renderSnakeColorOptions();
	ImGui::GetWindowDrawList()->ChannelsMerge();

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
	ImGui::SetCursorPosY(resolution.height * 0.02f);
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
	ImGui::SetCursorPosY(window.height * 0.2f);
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

	if (m_shouldResolutionTreeClose)
	{
		ImGui::SetNextItemOpen(false, ImGuiCond_Always);
		m_shouldResolutionTreeClose = false;
	}

	if (m_isResolutionTreeHovered)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 200, 0, 255));
	}
	else
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));

	if (ImGui::TreeNode(m_selectedResolutionName.c_str()))
	{
		m_isResolutionTreeHovered = ImGui::IsItemHovered();
		ImGui::Indent(window.width * 0.7f);
		ImGui::Indent();
		int index = 0;
		for (const auto resolution : m_resolutions)
		{
			ImVec2 posMin = ImGui::GetCursorScreenPos();
			ImVec2 itemSize = ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetFrameHeight());
			ImVec2 posMax = ImVec2(posMin.x + itemSize.x, posMin.y + itemSize.y);
			posMin.x -= 5;
			posMax.x += 5;

			ImU32 bgColor = IM_COL32(0, 0, 0, 255);
			ImGui::GetWindowDrawList()->AddRectFilled(posMin, posMax, bgColor);

			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 0));
			if (ImGui::Selectable(resolution.first.c_str(), resolution.first == m_selectedResolutionName))
			{
				m_selectedResolutionName = resolution.first;
				m_shouldResolutionTreeClose = true;
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
	else
	{
		m_isResolutionTreeHovered = ImGui::IsItemHovered();
	}

	ImGui::PopStyleColor(1);
}

void ui::OptionsSceneUI::renderFullscreenOption()
{
	const auto& window = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::PushFont(m_fonts["regular_font"]);
	ImGui::SetCursorPosX(window.width * 0.1f);
	ImGui::SetCursorPosY(window.height * 0.3f);

	ImGui::Text("Fullscreen");

	ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(80, 80, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(120, 120, 120, 255));
	ImGui::PushStyleColor(ImGuiCol_CheckMark, IM_COL32(255, 215, 0, 255));

	ImGui::SameLine();
	ImGui::Indent(window.width * 0.7f);
	ImGui::Checkbox("##FullscreenCheckbox", &m_isFullscreen);

	ImGui::PopStyleColor(4);
	ImGui::PopFont();
}

void ui::OptionsSceneUI::renderSnakeColorOptions()
{
	const auto& window = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::PushFont(m_fonts["regular_font"]);
	ImGui::SetCursorPosX(window.width * 0.1f);
	ImGui::SetCursorPosY(window.height * 0.4f);
	ImGui::Text("Player 1 snake color");
	ImGui::PopFont();

	ImGui::PushFont(m_fonts["smallish_font"]);
	ImGui::SetCursorPosX(window.width * 0.72f);
	ImGui::SetCursorPosY(window.height * 0.41f);
	ImGui::ColorEdit4("##Player1SnakeColor", &m_snake1Color.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	ImGui::PopFont();
	
	ImGui::PushFont(m_fonts["regular_font"]);
	ImGui::SetCursorPosX(window.width * 0.1f);
	ImGui::SetCursorPosY(window.height * 0.5f);
	ImGui::Text("Player 2 snake color");
	ImGui::PopFont();

	ImGui::PushFont(m_fonts["smallish_font"]);
	ImGui::SetCursorPosX(window.width * 0.72f);
	ImGui::SetCursorPosY(window.height * 0.51f);
	ImGui::ColorEdit4("Player 2 Snake Color", &m_snake2Color.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	ImGui::PopFont();
}
