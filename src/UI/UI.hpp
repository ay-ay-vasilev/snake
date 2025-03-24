#pragma once

#include <SDL3_image/SDL_image.h>
#include <string>

struct UIText
{
	int x;
	int y;
	double scale;
	std::string text;
};

class UI
{
public:
	UI() {}

	void init(std::pair<int, int> offset = {});
	void update();
	void render(SDL_Renderer* renderer);

	void addScore(int value);
	void setGameStateText(const std::string_view& text);
	void setDebugText(const std::string_view& text);

private:
	void renderUIText(SDL_Renderer* renderer, const UIText& uiText);

	UIText m_scoreText{};
	UIText m_gameStateText{};
	UIText m_debugText{};
	int m_score{0};
	std::pair<int, int> m_offset{};
};