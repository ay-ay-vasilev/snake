#include "GameState.hpp"

#include "../GameObjects.hpp"

GameState& changeState(GameState& currentState, GameState& newState, std::unique_ptr<GameObjects>& gameObjects)
{
	currentState.onExit(gameObjects);
	newState.onEnter(gameObjects);
	return newState;
}