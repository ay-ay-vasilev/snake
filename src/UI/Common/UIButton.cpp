#include "UIButton.hpp"

ui::UIButton::UIButton(
		ImVec2 position,
		ImVec2 size,
		ImVec2 origin,
		std::string buttonId,
		std::string label,
		std::function<void()> callback
	) : m_buttonSize(size), m_origin(origin), m_buttonId(buttonId), m_label(label), m_callback(callback)
{
	m_buttonPos = ImVec2( position.x - size.x * m_origin.x, position.y - size.y * m_origin.y);
	m_textColor = IM_COL32(255, 255, 255, 255);
}

void ui::UIButton::renderButton()
{
	m_isHovered = false;

	ImGui::SetCursorPosX(m_buttonPos.x);
	ImGui::SetCursorPosY(m_buttonPos.y);
	if (ImGui::InvisibleButton(m_buttonId.c_str(), m_buttonSize))
	{
		m_isSelected = true;
		if (m_callback) m_callback();
	}

	if (ImGui::IsItemHovered())
	{
		m_isSelected = true;
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
	m_textPos = ImVec2(
		m_buttonPos.x + (m_buttonSize.x - textSize.x) * 0.5f,
		m_buttonPos.y + (m_buttonSize.y - textSize.y) * 0.5f
	);
	ImGui::GetWindowDrawList()->AddText(m_textPos, m_textColor, m_label.c_str());
}

void ui::UIButton::press()
{
	m_textColor = IM_COL32(255, 100, 0, 255);
}
