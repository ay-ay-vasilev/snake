#include "LoseState.hpp"
#include "../GameObjects.hpp"
#include "StartState.hpp"

state::GameState& state::LoseState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->getUI()->update();
	return loseState;
}

void state::LoseState::render(SDL_Renderer* renderer, std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->render(renderer);
}

state::GameState& state::LoseState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		default:
			return changeState(startState, gameObjects);
			break;
		}
	}

	return loseState;
}

void state::LoseState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->getSnake()->undoMove();
	gameObjects->getUI()->setGameStateText("LOSE");
}

void state::LoseState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}