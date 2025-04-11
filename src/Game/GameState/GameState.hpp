#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include "../../Abstract/Subject.hpp"

class SDL_Renderer;
class GameObjects;
class Grid;

namespace state
{
	enum class StateType { eStart, ePlay, ePause, eLose };

	class GameState : public Subject
	{
	public:
		GameState() {};
		virtual ~GameState() override = default;
		virtual StateType update() = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		virtual StateType handleInput(void* appstate, SDL_Event* event) = 0;
		virtual void onEnter() = 0;
		virtual void onExit() = 0;

		virtual const StateType& getStateType() const { return m_type; };
		void setGameObjects(std::shared_ptr<GameObjects> gameObjects) { m_gameObjects = gameObjects; }
	protected:
		void setStateType(const StateType& type) { m_type = type; }
		std::shared_ptr<GameObjects> m_gameObjects;
	private:
		StateType m_type;
	};
}