#pragma once

#include "GameState.hpp"

class SDL_Renderer;

namespace state
{
	class PauseState : public GameState
	{
	public:
		PauseState(GameContextRef gameContext) : GameState(gameContext)
		{
			setStateType(StateType::ePause);
		};
		~PauseState() override = default;

		std::optional<StateType> update() override;
		void render(SDL_Renderer* renderer) override;
		std::optional<StateType> handleInput(void* appstate, SDL_Event* event) override;
		void onEnter() override;
		void onExit() override;
	};
}
