#pragma once

#include <SDL3_image/SDL_image.h>
#include <string>

class UI
{
public:
	UI() {}

	void init(std::pair<int, int> offset = {});
	void update();
	void render(SDL_Renderer* renderer);

	void addScore(int value);
	void setPaused(bool value);

private:
	std::string scoreText_{};
	std::string pausedText_{};
	int score_{0};
	bool isPaused_{false};
	std::pair<int, int> offset_{};
};