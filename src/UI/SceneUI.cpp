#include "SceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"

#include "../Game/GameContext.hpp"
#include "../Data/DataManager.hpp"
#include "../Options/OptionsManager.hpp"

void ui::initUIText(const data::TextData& textData, ui::UIText& uiText)
{
	uiText.x = textData.x;
	uiText.y = textData.y;
	uiText.scale = textData.scale;
}

void ui::SceneUI::setCommandCallback(std::function<void(ui::UICommand)> callback)
{
	m_commandCallback = std::move(callback);
}

void ui::SceneUI::renderButtons()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();

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
	
	ImGui::SetCursorPosY(resolution.height * 0.5f);

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

	handleKeyboardPresses();

	for (auto& button : m_buttons)
		button.renderText();

	ImGui::PopFont();
}

void ui::SceneUI::handleKeyboardPresses()
{
	if (m_isSelectionBusy)
	{
		if (ImGui::IsKeyDown(ImGuiKey_Enter) || ImGui::IsKeyDown(ImGuiKey_Space))
		{
			m_isSelectionBusy = false;
			return;
		}
		return;
	}

	if (ImGui::IsKeyDown(ImGuiKey_Enter) || ImGui::IsKeyDown(ImGuiKey_Space) || ImGui::IsKeyDown(ImGuiKey_E))
		m_buttons.at(m_selectedIndex).press();
	if (ImGui::IsKeyReleased(ImGuiKey_Enter) || ImGui::IsKeyReleased(ImGuiKey_Space) || ImGui::IsKeyReleased(ImGuiKey_E))
		m_buttons.at(m_selectedIndex).activate();
}
