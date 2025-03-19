#pragma once

#include <SDL3_image/SDL_image.h>
#include <string>

class UI
{
public:
	UI(std::pair<int, int> offset) : offset(offset) {}

	void init();
	void update();
	void render(SDL_Renderer* renderer);

	void addScore(int value);
	void setDirection(int direction);

private:
	std::string scoreText{};
	std::string directionText{};
	int score{0};
	std::pair<int, int> offset;
};