#pragma once

#include "imgui.h"
#include <functional>
#include <string>

namespace ui
{
class UIButton
{
public:
	explicit UIButton(
		ImVec2 position,
		ImVec2 size,
		ImVec2 origin,
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
	ImVec2 m_buttonPos{0.f, 0.f};
	ImVec2 m_buttonSize{0.f, 0.f};
	ImVec2 m_origin{0.f, 0.f};
	ImVec2 m_textPos{0.f, 0.f};
	ImU32 m_textColor;
	std::string m_buttonId;
	std::string m_label;
	std::function<void()> m_callback;
	bool m_isSelected{false};
	bool m_isHovered{false};
};
}
