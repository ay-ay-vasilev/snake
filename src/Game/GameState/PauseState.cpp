#include "PauseState.hpp"
#include "../GameObjects.hpp"
#include "../../UI/UI.hpp"
#include "PlayState.hpp"
#include "StartState.hpp"

GameState& PauseState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->update();
	return pauseState;
}

GameState& PauseState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_SPACE:
			return changeState(pauseState, playState, gameObjects);
			break;
		case SDLK_R:
			return changeState(pauseState, startState, gameObjects);
			break;
		default:
			break;
		}
	}

	return pauseState;
}

void PauseState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->setGameStateText("PAUSED");
}

void PauseState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}