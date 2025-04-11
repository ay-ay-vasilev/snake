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
		virtual StateType update(std::unique_ptr<GameObjects>& gameObjects) = 0;
		virtual void render(SDL_Renderer* renderer, std::unique_ptr<GameObjects>& gameObjects) = 0;
		virtual StateType handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects) = 0;
		virtual void onEnter(std::unique_ptr<GameObjects>& gameObjects) = 0;
		virtual void onExit(std::unique_ptr<GameObjects>& gameObjects) = 0;

		virtual const StateType& getStateType() const { return m_type; };
	protected:
		void setStateType(const StateType& type) { m_type = type; }
		
	private:
		StateType m_type;
	};
}