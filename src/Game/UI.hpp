#pragma once

#include <string>

class SDL_Renderer;

class UI
{
public:
	void init();
	void update();
	void render(SDL_Renderer* renderer);

	void addScore(int value);

private:
	std::string scoreText{};
	int score{0};
	std::pair<int, int> offset;
};