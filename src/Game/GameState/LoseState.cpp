#include "LoseState.hpp"
#include "../GameObjects.hpp"
#include "StartState.hpp"

state::StateType state::LoseState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	return state::StateType::eLose;
}

void state::LoseState::render(SDL_Renderer* renderer, std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->render(renderer);
}

state::StateType state::LoseState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_R:
			return state::StateType::eStart;
			break;
		}
	}

	return state::StateType::eLose;
}

void state::LoseState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->getSnake()->undoMove();
	CreateMessage(ObserverMessageType::eGameState, std::string("LOSE"));
}

void state::LoseState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}