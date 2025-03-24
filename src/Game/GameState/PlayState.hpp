#pragma once

#include "GameState.hpp"

static bool checkCollision(std::unique_ptr<Grid>& grid, const std::pair<int, int>& position);

class PlayState : public GameState
{
public:
	PlayState() = default;
	~PlayState() override = default;

	GameState& update(std::unique_ptr<GameObjects>& gameObjects) override;
	GameState& handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects) override;
	void onEnter(std::unique_ptr<GameObjects>& gameObjects) override;
	void onExit(std::unique_ptr<GameObjects>& gameObjects) override;
};

static PlayState playState = PlayState();