#include "GameState.hpp"

#include "../GameObjects.hpp"

state::GameState& state::GameState::changeState(state::GameState& newState, std::unique_ptr<GameObjects>& gameObjects)
{
	onExit(gameObjects);
	newState.onEnter(gameObjects);
	return newState;
}