#include "PauseState.hpp"
#include "../GameObjects.hpp"
#include "PlayState.hpp"
#include "StartState.hpp"

state::StateType state::PauseState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	return state::StateType::ePause;
}

void state::PauseState::render(SDL_Renderer* renderer, std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->render(renderer);
}

state::StateType state::PauseState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_SPACE:
			return state::StateType::ePlay;
			break;
		case SDLK_R:
			return state::StateType::eStart;
			break;
		default:
			break;
		}
	}

	return state::StateType::ePause;
}

void state::PauseState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	CreateMessage(ObserverMessageType::eGameState, std::string("PAUSED"));
}

void state::PauseState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}