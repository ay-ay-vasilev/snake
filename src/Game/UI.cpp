#include "UI.hpp"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Constants.hpp"

void UI::init()
{
	offset =
	{
		TEXT_X + (WINDOW_WIDTH - GRID_SIZE * CELL_SIZE) / 2,
		TEXT_Y + (WINDOW_HEIGHT - GRID_SIZE * CELL_SIZE) / 2
	};
}

void UI::update()
{
	scoreText = "Score: " + std::to_string(score);
}

void UI::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, TEXT_SCALE, TEXT_SCALE);
	SDL_RenderDebugText(renderer, offset.first / TEXT_SCALE, offset.second / TEXT_SCALE, scoreText.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);
}

void UI::addScore(int value)
{
	score += value;
}