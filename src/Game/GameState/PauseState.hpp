#pragma once

#include "GameState.hpp"

class PauseState : public GameState
{
public:
	PauseState() = default;
	~PauseState() override = default;

	GameState& update(std::unique_ptr<GameObjects>& gameObjects) override;
	GameState& handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects) override;
	void onEnter(std::unique_ptr<GameObjects>& gameObjects) override;
	void onExit(std::unique_ptr<GameObjects>& gameObjects) override;
};

static PauseState pauseState = PauseState();