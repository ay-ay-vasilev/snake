#include "PauseState.hpp"

std::optional<state::StateType> state::PauseState::update()
{
	return std::nullopt;
}

void state::PauseState::render(SDL_Renderer* renderer)
{
	m_gameObjects->render(renderer);
}

std::optional<state::StateType> state::PauseState::handleInput(void* appstate, SDL_Event* event)
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

	return std::nullopt;
}

void state::PauseState::onEnter()
{
	createMessage(ObserverMessageType::eGameState, std::string("PAUSED"));
}

void state::PauseState::onExit() {}
