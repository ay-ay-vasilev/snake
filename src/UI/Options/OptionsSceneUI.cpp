#include "OptionsSceneUI.hpp"

#include "imgui.h"
#include <SDL3_image/SDL_image.h>

#include "../UICommand.hpp"
#include "../../Scenes/Scene.hpp"
#include "../../Game/GameContext.hpp"

static ImVec4 getImVec4FromColor(options::Color color)
{
	return
	{
		(color.r / 255.f),
		(color.g / 255.f),
		(color.b / 255.f),
		(color.a / 255.f),
	};
}

static options::Color getColorFromImVec4(ImVec4 color)
{
	return
	{
		static_cast<int>(color.x * 255.f),
		static_cast<int>(color.y * 255.f),
		static_cast<int>(color.z * 255.f),
		static_cast<int>(color.w * 255.f)
	};
}

void ui::OptionsSceneUI::init()
{
	auto& optionsManager = m_gameContext->getOptionsManager();

	m_resolutions = optionsManager->getResolutionPresets();
	m_selectedResolutionName = optionsManager->getCurrentResolution().name;
	m_isFullscreen = optionsManager->getIsFullscreen();

	const auto& snake1Color = optionsManager->getSnake1Color();
	m_snake1Color = getImVec4FromColor(snake1Color);
	const auto& snake2Color = optionsManager->getSnake2Color();
	m_snake2Color = getImVec4FromColor(snake2Color);

	m_selectedGameSpeed = optionsManager->getGameSpeedStr();
	m_gameSpeedPresets = optionsManager->getGameSpeedPresetsStr();

	m_buttons.emplace_back
		(
			UIButton(
				m_gameContext, ImVec2(),
				ImVec2(0.1f, 0.9f), ImVec2(200, 80), ImVec2(0.f, 0.5f),
				std::string("##backBtn"), std::string("Back"),
				[this]()
				{
					m_shouldResolutionTreeClose = true;
					m_shouldGameSpeedTreeClose = true;
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
					m_shouldGameSpeedTreeClose = true;
					m_snake1Color = getImVec4FromColor(optionsManager->getSnake1Color());
					m_snake2Color = getImVec4FromColor(optionsManager->getSnake2Color());
					m_selectedGameSpeed = optionsManager->getGameSpeedStr();
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
					optionsManager->setSnake1Color(getColorFromImVec4(m_snake1Color));
					optionsManager->setSnake2Color(getColorFromImVec4(m_snake2Color));
					optionsManager->setGameSpeed(m_selectedGameSpeed);
					optionsManager->saveOptions();
					m_shouldResolutionTreeClose = true;
					m_shouldGameSpeedTreeClose = true;
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
	renderResolutionsOptions();
	renderFullscreenOption();
	renderGameSpeedOptions();

	ImGui::GetWindowDrawList()->ChannelsSetCurrent(0);
	renderSnakeColorOptions();
	renderButtons();
	ImGui::GetWindowDrawList()->ChannelsMerge();

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

void ui::OptionsSceneUI::renderResolutionsOptions()
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
	ImGui::ColorEdit4("##Player1SnakeColor", (float*)&m_snake1Color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	ImGui::PopFont();
	
	ImGui::PushFont(m_fonts["regular_font"]);
	ImGui::SetCursorPosX(window.width * 0.1f);
	ImGui::SetCursorPosY(window.height * 0.5f);
	ImGui::Text("Player 2 snake color");
	ImGui::PopFont();

	ImGui::PushFont(m_fonts["smallish_font"]);
	ImGui::SetCursorPosX(window.width * 0.72f);
	ImGui::SetCursorPosY(window.height * 0.51f);
	ImGui::ColorEdit4("Player 2 Snake Color", (float*)&m_snake2Color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	ImGui::PopFont();
}

void ui::OptionsSceneUI::renderGameSpeedOptions()
{
	const auto& window = m_gameContext->getOptionsManager()->getCurrentResolution();

	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));

	ImGui::SetCursorPosX(window.width * 0.1f);
	ImGui::SetCursorPosY(window.height * 0.6f);
	ImGui::PushFont(m_fonts["regular_font"]);
	ImGui::Text("Game speed:");
	ImGui::SameLine(window.width * 0.7f);
	renderGameSpeedTreeNode();
	ImGui::PopFont();
	ImGui::PopStyleColor(3);
}

void ui::OptionsSceneUI::renderGameSpeedTreeNode()
{
	const auto& window = m_gameContext->getOptionsManager()->getCurrentResolution();

	if (m_shouldGameSpeedTreeClose)
	{
		ImGui::SetNextItemOpen(false, ImGuiCond_Always);
		m_shouldGameSpeedTreeClose = false;
	}

	if (m_isGameSpeedTreeHovered)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 200, 0, 255));
	}
	else
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));

	if (ImGui::TreeNode(m_selectedGameSpeed.c_str()))
	{
		m_isGameSpeedTreeHovered = ImGui::IsItemHovered();
		ImGui::Indent();
		ImGui::Indent();
		int index = 0;
		for (const auto& gameSpeed : m_gameSpeedPresets)
		{
			ImVec2 posMin = ImGui::GetCursorScreenPos();
			ImVec2 itemSize = ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetFrameHeight());
			ImVec2 posMax = ImVec2(posMin.x + itemSize.x, posMin.y + itemSize.y);
			posMin.x -= 5;
			posMax.x += 5;

			ImU32 bgColor = IM_COL32(0, 0, 0, 255);
			ImGui::GetWindowDrawList()->AddRectFilled(posMin, posMax, bgColor);

			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 0));
			if (ImGui::Selectable(gameSpeed.c_str(), gameSpeed == m_selectedGameSpeed))
			{
				m_selectedGameSpeed = gameSpeed;
				m_shouldGameSpeedTreeClose = true;
			}
			ImGui::PopStyleColor(1);

			ImVec2 itemMin = ImGui::GetItemRectMin();
			ImVec2 itemMax = ImGui::GetItemRectMax();
			ImVec2 textPos = ImVec2(itemMin.x, itemMin.y + ImGui::GetStyle().FramePadding.y);

			ImU32 textColor = IM_COL32(255, 255, 255, 255); // Default
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
				textColor = IM_COL32(255, 165, 0, 255); // Orange
			else if (gameSpeed == m_selectedGameSpeed)
				textColor = IM_COL32(255, 255, 0, 255); // Yellow

			ImGui::GetWindowDrawList()->AddText(textPos, textColor, gameSpeed.c_str());
			++index;
		}
		ImGui::Unindent();
		ImGui::Unindent();
		ImGui::TreePop();
	}
	else
	{
		m_isGameSpeedTreeHovered = ImGui::IsItemHovered();
	}

	ImGui::PopStyleColor(1);
}
