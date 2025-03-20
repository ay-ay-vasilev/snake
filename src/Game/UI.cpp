#include "UI.hpp"

#include "Constants.hpp"

void UI::init(std::pair<int, int> offset)
{
	offset_ = offset;
	pausedText_ = "PAUSED";
}

void UI::update()
{
	scoreText_ = "Score: " + std::to_string(score_);
}

void UI::render(SDL_Renderer* renderer)
{
	using namespace constants;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, TEXT_SCORE_SCALE, TEXT_SCORE_SCALE);
	SDL_RenderDebugText(renderer,
		(TEXT_SCORE_X + offset_.first) / TEXT_SCORE_SCALE,
		(TEXT_SCORE_Y + offset_.second) / TEXT_SCORE_SCALE,
		scoreText_.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);

	if (isPaused_)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_SetRenderScale(renderer, TEXT_DIRECTION_SCALE, TEXT_DIRECTION_SCALE);
		SDL_RenderDebugText(renderer,
			(TEXT_DIRECTION_X + offset_.first) / TEXT_DIRECTION_SCALE,
			(TEXT_DIRECTION_Y + offset_.second) / TEXT_DIRECTION_SCALE,
			pausedText_.c_str());
		SDL_SetRenderScale(renderer, 1.f, 1.f);
	}
}

void UI::addScore(int value)
{
	score_ += value;
}

void UI::setPaused(bool value)
{
	isPaused_ = value;
}