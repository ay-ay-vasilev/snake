#include "LoseState.hpp"
#include "../GameObjects.hpp"
#include "../../UI/UI.hpp"
#include "StartState.hpp"

GameState& LoseState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->update();
	return loseState;
}

GameState& LoseState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		default:
			return changeState(loseState, startState, gameObjects);
			break;
		}
	}

	return loseState;
}

void LoseState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->setGameStateText("LOSE");
}

void LoseState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}