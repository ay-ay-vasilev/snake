#pragma once

#include "GameState.hpp"

class SDL_Renderer;

namespace state
{
	class PauseState : public GameState
	{
	public:
		PauseState()
		{
			setStateType(StateType::ePause);
		};
		~PauseState() override = default;

		StateType update() override;
		void render(SDL_Renderer* renderer) override;
		StateType handleInput(void* appstate, SDL_Event* event) override;
		void onEnter() override;
		void onExit() override;
	};
}