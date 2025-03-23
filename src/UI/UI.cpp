#include "UI.hpp"
#include "../Constants/Constants.hpp"

void initUIText(const constants::TextData& textData, UIText& uiText)
{
	uiText.x = textData.x;
	uiText.y = textData.y;
	uiText.scale = textData.scale;
}

void UI::init(std::pair<int, int> offset)
{
	auto& dataManager = constants::DataManager::getInstance();

	const auto& scoreTextData = dataManager.getConstant<constants::TextData>("score_text");
	const auto& gameStateTextData = dataManager.getConstant<constants::TextData>("game_state_text");
	const auto& debugTextData = dataManager.getConstant<constants::TextData>("debug_text");

	initUIText(scoreTextData, scoreText_);
	initUIText(gameStateTextData, gameStateText_);
	initUIText(debugTextData, debugText_);

	offset_ = offset;
	gameStateText_.text = "START";
	debugText_.text = "DEBUG";
}

void UI::update()
{
	scoreText_.text = "Score: " + std::to_string(score_);
}

void UI::render(SDL_Renderer* renderer)
{
	renderUIText(renderer, scoreText_);
	renderUIText(renderer, gameStateText_);
	renderUIText(renderer, debugText_);
}

void UI::renderUIText(SDL_Renderer* renderer, const UIText& uiText)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, uiText.scale, uiText.scale);
	SDL_RenderDebugText(renderer,
		(uiText.x + offset_.first) / uiText.scale,
		(uiText.y + offset_.second) / uiText.scale,
		uiText.text.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);
}

void UI::addScore(int value)
{
	score_ += value;
}

void UI::setGameStateText(const std::string_view& text)
{
	gameStateText_.text = text;
}

void UI::setDebugText(const std::string_view& text)
{
	debugText_.text = text;
}