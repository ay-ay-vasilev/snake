#include "UI.hpp"

#include "../Constants/Constants.hpp"

void UI::init(std::pair<int, int> offset)
{
	auto& dataManager = constants::DataManager::getInstance();
	const auto& scoreTextData = dataManager.getConstant<constants::TextData>("score_text");
	scoreText_.x = scoreTextData.x;
	scoreText_.y = scoreTextData.y;
	scoreText_.scale = scoreTextData.scale;

	const auto& gameStateTextData = dataManager.getConstant<constants::TextData>("game_state_text");
	gameStateText_.x = gameStateTextData.x;
	gameStateText_.y = gameStateTextData.y;
	gameStateText_.scale = gameStateTextData.scale;

	const auto& debugTextData = dataManager.getConstant<constants::TextData>("debug_text");
	debugText_.x = debugTextData.x;
	debugText_.y = debugTextData.y;
	debugText_.scale = debugTextData.scale;

	offset_ = offset;
	gameStateText_.text = "PAUSED";
	debugText_.text = "DEBUG";
}

void UI::update()
{
	scoreText_.text = "Score: " + std::to_string(score_);
}

void UI::render(SDL_Renderer* renderer)
{
	using namespace constants;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, scoreText_.scale, scoreText_.scale);
	SDL_RenderDebugText(renderer,
		(scoreText_.x + offset_.first) / scoreText_.scale,
		(scoreText_.y + offset_.second) / scoreText_.scale,
		scoreText_.text.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);

	if (isPaused_)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_SetRenderScale(renderer, gameStateText_.scale, gameStateText_.scale);
		SDL_RenderDebugText(renderer,
			(gameStateText_.x + offset_.first) / gameStateText_.scale,
			(gameStateText_.y + offset_.second) / gameStateText_.scale,
			gameStateText_.text.c_str());
		SDL_SetRenderScale(renderer, 1.f, 1.f);
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, debugText_.scale, debugText_.scale);
	SDL_RenderDebugText(renderer,
		(debugText_.x + offset_.first) / debugText_.scale,
		(debugText_.y + offset_.second) / debugText_.scale,
		debugText_.text.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);
}

void UI::addScore(int value)
{
	score_ += value;
}

void UI::setPaused(bool value)
{
	isPaused_ = value;
}

void UI::setDebugText(const std::string_view& text)
{
	debugText_.text = text;
}