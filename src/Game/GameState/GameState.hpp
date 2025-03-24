#pragma once

#include <SDL3/SDL.h>

#include <memory>

class SDL_Renderer;
class GameObjects;
class Grid;

namespace state
{
	class GameState
	{
	public:
		GameState() = default;
		virtual ~GameState() = default;
		virtual GameState& update(std::unique_ptr<GameObjects>& gameObjects) = 0;
		virtual void render(SDL_Renderer* renderer, std::unique_ptr<GameObjects>& gameObjects) = 0;
		virtual GameState& handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects) = 0;
		virtual void onEnter(std::unique_ptr<GameObjects>& gameObjects) = 0;
		virtual void onExit(std::unique_ptr<GameObjects>& gameObjects) = 0;

		GameState& changeState(GameState& newState, std::unique_ptr<GameObjects>& gameObjects);
	};
}