#pragma once

#include "GameState.hpp"

class StartState : public GameState
{
public:
	StartState() = default;
	~StartState() override = default;

	GameState& update(std::unique_ptr<GameObjects>& gameObjects) override;
	GameState& handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects) override;
	void onEnter(std::unique_ptr<GameObjects>& gameObjects) override;
	void onExit(std::unique_ptr<GameObjects>& gameObjects) override;
};

static StartState startState = StartState();