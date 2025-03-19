#include "UI.hpp"

#include "Constants.hpp"

void UI::init() {}

void UI::update()
{
	scoreText = "Score: " + std::to_string(score);
}

void UI::render(SDL_Renderer* renderer)
{
	using namespace constants;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, TEXT_SCORE_SCALE, TEXT_SCORE_SCALE);
	SDL_RenderDebugText(renderer,
		(TEXT_SCORE_X + offset.first) / TEXT_SCORE_SCALE,
		(TEXT_SCORE_Y + offset.second) / TEXT_SCORE_SCALE,
		scoreText.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, TEXT_DIRECTION_SCALE, TEXT_DIRECTION_SCALE);
	SDL_RenderDebugText(renderer,
		(TEXT_DIRECTION_X + offset.first) / TEXT_DIRECTION_SCALE,
		(TEXT_DIRECTION_Y + offset.second) / TEXT_DIRECTION_SCALE,
		directionText.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);
}

void UI::addScore(int value)
{
	score += value;
}

void UI::setDirection(int direction)
{
	switch (direction)
	{
	case 0:
		directionText = "UP";
		break;
	case 1:
		directionText = "RIGHT";
		break;
	case 2:
		directionText = "DOWN";
		break;
	case 3:
		directionText = "LEFT";
		break;	
	default:
		directionText = "NONE";
		break;
	}
}