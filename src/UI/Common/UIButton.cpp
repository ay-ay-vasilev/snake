#include "UIButton.hpp"

#include "../../Game/GameContext.hpp"

ui::UIButton::UIButton(
		GameContextRef gameContext,
		ImVec2 offset,
		ImVec2 relativePosition,
		ImVec2 size,
		ImVec2 origin,
		std::string buttonId,
		std::string label,
		std::function<void()> callback
	) : m_gameContext(gameContext), m_buttonRelativePos(relativePosition), m_buttonSize(size), m_origin(origin), m_buttonId(buttonId), m_label(label), m_callback(callback)
{
	m_buttonOffset = ImVec2( offset.x - size.x * m_origin.x, offset.y - size.y * m_origin.y);
	m_textColor = IM_COL32(255, 255, 255, 255);
}

void ui::UIButton::renderButton()
{
	m_isHovered = false;

	const auto& optionsManager = m_gameContext->getOptionsManager();
	const auto& windowSize = optionsManager->getCurrentResolution();
	const ImVec2 buttonPos =
	{
			windowSize.width * m_buttonRelativePos.x + m_buttonOffset.x, 
			windowSize.height * m_buttonRelativePos.y + m_buttonOffset.y 
	};
	ImGui::SetCursorPosX(buttonPos.x);
	ImGui::SetCursorPosY(buttonPos.y);
	if (ImGui::InvisibleButton(m_buttonId.c_str(), m_buttonSize))
	{
		m_isSelected = true;
		if (m_callback) m_callback();
	}

	if (ImGui::IsItemHovered())
	{
		m_isHovered = true;
	}

	if (m_isSelected && !ImGui::IsItemActive())
		m_textColor = IM_COL32(255, 180, 0, 255);
	else if (ImGui::IsItemActive())
		m_textColor = IM_COL32(255, 100, 0, 255);
	else
		m_textColor = IM_COL32(255, 255, 255, 255);
}

void ui::UIButton::renderText()
{
	const auto textSize = ImGui::CalcTextSize(m_label.c_str());

	const auto& optionsManager = m_gameContext->getOptionsManager();
	const auto& windowSize = optionsManager->getCurrentResolution();
	const ImVec2 buttonPos =
	{
			windowSize.width * m_buttonRelativePos.x + m_buttonOffset.x, 
			windowSize.height * m_buttonRelativePos.y + m_buttonOffset.y 
	};

	m_textPos = ImVec2(
		buttonPos.x + (m_buttonSize.x - textSize.x) * 0.5f,
		buttonPos.y + (m_buttonSize.y - textSize.y) * 0.5f
	);
	ImGui::GetWindowDrawList()->AddText(m_textPos, m_textColor, m_label.c_str());
}

void ui::UIButton::press()
{
	m_textColor = IM_COL32(255, 100, 0, 255);
}
