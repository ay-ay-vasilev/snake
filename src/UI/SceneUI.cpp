#include "SceneUI.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"

#include "../Game/GameContext.hpp"

void ui::SceneUI::setCommandCallback(std::function<void(ui::UICommand)> callback)
{
	m_commandCallback = std::move(callback);
}

void ui::SceneUI::renderButtons()
{
	if (m_buttons.empty())
		return;

	detectInputSource();
	updateSelection();
	syncButtonStates();
	layoutButtons();
	renderAllButtons();
}

void ui::SceneUI::detectInputSource()
{
	ImGuiIO& io = ImGui::GetIO();

	if (ImGui::IsKeyPressed(ImGuiKey_UpArrow) ||
		ImGui::IsKeyPressed(ImGuiKey_DownArrow) ||
		ImGui::IsKeyPressed(ImGuiKey_W) ||
		ImGui::IsKeyPressed(ImGuiKey_S))
	{
		m_lastInput = eInputSource::Keyboard;
	}

	if (io.MouseDelta.x != 0.0f || io.MouseDelta.y != 0.0f || ImGui::IsMouseClicked(0))
	{
		m_lastInput = eInputSource::Mouse;
	}
}

void ui::SceneUI::updateSelection()
{
	if (m_lastInput == eInputSource::Keyboard)
	{
		if (ImGui::IsKeyPressed(ImGuiKey_S) || ImGui::IsKeyPressed(ImGuiKey_DownArrow))
			m_selectedIndex = (m_selectedIndex + 1) % m_buttons.size();

		if (ImGui::IsKeyPressed(ImGuiKey_W) || ImGui::IsKeyPressed(ImGuiKey_UpArrow))
			m_selectedIndex = (m_selectedIndex - 1 + m_buttons.size()) % m_buttons.size();
	}
	else if (m_lastInput == eInputSource::Mouse)
	{
		for (int i = 0; i < m_buttons.size(); i++)
		{
				if (m_buttons[i].isHovered())
				{
					m_selectedIndex = i;
					break;
				}
		}
	}
}

void ui::SceneUI::syncButtonStates()
{
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].setIsSelected(i == m_selectedIndex);
	}
}

void ui::SceneUI::handleInput()
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

void ui::SceneUI::layoutButtons()
{
	const auto& resolution = m_gameContext->getOptionsManager()->getCurrentResolution();
	ImGui::SetCursorPosY(resolution.height * 0.5f);
}

void ui::SceneUI::renderAllButtons()
{
	ImGui::PushFont(m_fonts["regular_font"]);

	for (auto& button : m_buttons)
		button.renderButton();

	handleInput();

	for (auto& button : m_buttons)
		button.renderText();

	ImGui::PopFont();
}
