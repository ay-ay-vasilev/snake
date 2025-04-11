#pragma once

#include "GameState.hpp"

class SDL_Renderer;

namespace state
{
	class LoseState : public GameState
	{
	public:
		LoseState()
		{
			setStateType(StateType::eLose);
		};
		~LoseState() override = default;

		StateType update() override;
		void render(SDL_Renderer* renderer) override;
		StateType handleInput(void* appstate, SDL_Event* event) override;
		void onEnter() override;
		void onExit() override;
	};
}