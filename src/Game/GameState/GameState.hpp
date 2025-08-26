#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <optional>
#include "../../Abstract/Subject.hpp"
#include "../GameObjects/GameObjects.hpp"

class SDL_Renderer;
class Grid;

namespace context
{
class GameContext;
}
using GameContextRef = std::unique_ptr<context::GameContext>&;

namespace state
{
	enum class StateType { eStart, ePlay, ePause, eLose };

	class GameState : public Subject
	{
	public:
		GameState(GameContextRef gameContext) : m_gameContext(gameContext) {};
		virtual ~GameState() override = default;
		virtual std::optional<StateType> update() = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		virtual std::optional<StateType> handleInput(void* appstate, SDL_Event* event) = 0;
		virtual void onEnter() = 0;
		virtual void onExit() = 0;

		virtual const StateType& getStateType() const { return m_type; };
		void setGameObjects(std::shared_ptr<GameObjects> gameObjects) { m_gameObjects = gameObjects; }
	protected:
		void setStateType(const StateType& type) { m_type = type; }
		std::shared_ptr<GameObjects> m_gameObjects;
		GameContextRef m_gameContext;
	private:
		StateType m_type;
	};
}
