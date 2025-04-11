#pragma once

#include "GameState.hpp"

class SDL_Renderer;

namespace state
{
	class StartState : public GameState
	{
	public:
		StartState()
		{
			setStateType(StateType::eStart);
		};
		~StartState() override = default;

		StateType update(std::unique_ptr<GameObjects>& gameObjects) override;
		void render(SDL_Renderer* renderer, std::unique_ptr<GameObjects>& gameObjects) override;
		StateType handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects) override;
		void onEnter(std::unique_ptr<GameObjects>& gameObjects) override;
		void onExit(std::unique_ptr<GameObjects>& gameObjects) override;
	};
}