#pragma once

#include <SDL3/SDL.h>

#include <memory>

class GameObjects;
class Grid;

class GameState
{
public:
	GameState() = default;
	virtual ~GameState() = default;
	virtual GameState& update(std::unique_ptr<GameObjects>& gameObjects) = 0;
	virtual GameState& handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects) = 0;
	virtual void onEnter(std::unique_ptr<GameObjects>& gameObjects) = 0;
	virtual void onExit(std::unique_ptr<GameObjects>& gameObjects) = 0;

	GameState& changeState(GameState& currentState, GameState& newState, std::unique_ptr<GameObjects>& gameObjects);
};

class PlayState : public GameState
{
public:
	PlayState() = default;
	~PlayState() override = default;

	GameState& update(std::unique_ptr<GameObjects>& gameObjects) override;
	GameState& handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects) override;
	void onEnter(std::unique_ptr<GameObjects>& gameObjects) override;
	void onExit(std::unique_ptr<GameObjects>& gameObjects) override;

private:
	bool checkCollision(std::unique_ptr<Grid>& grid, const std::pair<int, int>& position) const;
};

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

class LoseState : public GameState
{
public:
	LoseState() = default;
	~LoseState() override = default;

	GameState& update(std::unique_ptr<GameObjects>& gameObjects) override;
	GameState& handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects) override;
	void onEnter(std::unique_ptr<GameObjects>& gameObjects) override;
	void onExit(std::unique_ptr<GameObjects>& gameObjects) override;
};


static PlayState playState = PlayState();
static PauseState pauseState = PauseState();
static LoseState loseState = LoseState();
static StartState startState = StartState();