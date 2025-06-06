#pragma once

#include "GameState.hpp"

class SDL_Renderer;

namespace state
{
	class PlayState : public GameState
	{
	public:
		PlayState(GameContextRef gameContext) : GameState(gameContext)
		{
			setStateType(StateType::ePlay);
		};
		~PlayState() override = default;

		std::optional<StateType> update() override;
		void render(SDL_Renderer* renderer) override;
		std::optional<StateType> handleInput(void* appstate, SDL_Event* event) override;
		void onEnter() override;
		void onExit() override;
	};
}
