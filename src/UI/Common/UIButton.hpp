#pragma once

#include "imgui.h"
#include <functional>
#include <string>
#include <memory>

namespace context
{
	class GameContext;
}
using GameContextRef = std::unique_ptr<context::GameContext>&;

namespace ui
{
class UIButton
{
public:
	explicit UIButton(
		GameContextRef gameContext,
		ImVec2 offset,
		ImVec2 relativePosition,
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
	const std::string getButtonId() const { return m_buttonId; }
	
private:
	GameContextRef m_gameContext;
	ImVec2 m_buttonOffset{0.f, 0.f};
	ImVec2 m_buttonRelativePos{0.f, 0.f};
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
