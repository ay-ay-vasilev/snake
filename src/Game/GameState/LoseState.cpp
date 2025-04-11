#include "LoseState.hpp"
#include "../GameObjects.hpp"
#include "StartState.hpp"

state::StateType state::LoseState::update()
{
	return state::StateType::eLose;
}

void state::LoseState::render(SDL_Renderer* renderer)
{
	m_gameObjects->render(renderer);
}

state::StateType state::LoseState::handleInput(void* appstate, SDL_Event* event)
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

void state::LoseState::onEnter()
{
	m_gameObjects->getSnake()->undoMove();
	createMessage(ObserverMessageType::eGameState, std::string("LOSE"));
}

void state::LoseState::onExit() {}