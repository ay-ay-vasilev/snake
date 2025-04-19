#pragma once

#include "imgui.h"
#include <functional>
#include <string>

namespace ui
{
class MainMenuSceneUIButton
{
public:
	explicit MainMenuSceneUIButton(
		ImVec2 position,
		ImVec2 size,
		std::string buttonId,
		std::string label,
		std::function<void()> callback
	);

	void renderButton();
	void renderText();
	void press();
	void activate() { if (m_callback) m_callback(); }
	void setIsSelected(bool value) { m_isSelected = value; if (!value) m_textColor = IM_COL32(255, 255, 255, 255); }
	const bool isSelected() const { return m_isSelected; }
	const bool isHovered() const { return m_isHovered; }
	
private:
	ImVec2 m_buttonPos;
	ImVec2 m_buttonSize;
	ImVec2 m_textPos;
	ImU32 m_textColor;
	std::string m_buttonId;
	std::string m_label;
	std::function<void()> m_callback;
	bool m_isSelected{false};
	bool m_isHovered{false};
};
}
