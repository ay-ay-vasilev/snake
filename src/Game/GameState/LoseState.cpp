#include "LoseState.hpp"

std::optional<state::StateType> state::LoseState::update()
{
	return std::nullopt;
}

void state::LoseState::render(SDL_Renderer* renderer)
{
	m_gameObjects->render(renderer);
}

std::optional<state::StateType> state::LoseState::handleInput(void* appstate, SDL_Event* event)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_R:
			return state::StateType::eStart;
			break;
		case SDLK_SPACE:
			createMessage(ObserverMessageType::eChangeScene, std::string("SaveHighscore"));
			break;
		}
	}

	return std::nullopt;
}

void state::LoseState::onEnter()
{
	m_gameObjects->getSnake()->undoMove();
	createMessage(ObserverMessageType::eGameState, std::string("LOSE"));
}

void state::LoseState::onExit() {}
