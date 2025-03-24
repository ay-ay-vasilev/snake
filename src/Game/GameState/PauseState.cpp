#include "PauseState.hpp"
#include "../GameObjects.hpp"
#include "PlayState.hpp"
#include "StartState.hpp"

state::GameState& state::PauseState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->getUI()->update();
	return pauseState;
}

void state::PauseState::render(SDL_Renderer* renderer, std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->render(renderer);
}

state::GameState& state::PauseState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_SPACE:
			return changeState(playState, gameObjects);
			break;
		case SDLK_R:
			return changeState(startState, gameObjects);
			break;
		default:
			break;
		}
	}

	return pauseState;
}

void state::PauseState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->getUI()->setGameStateText("PAUSED");
}

void state::PauseState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}