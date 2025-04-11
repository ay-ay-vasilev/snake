#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <unordered_map>

class GameObjects;
class SDL_Renderer;

namespace state
{
	class GameState;
	enum class StateType;
}

class Game
{
public:
	Game();
	~Game();

	void init(SDL_Window* window, SDL_Renderer* renderer);
	SDL_AppResult handleInput(void* appstate, SDL_Event* event);
	SDL_AppResult gameLoop(void* appstate, SDL_Renderer* renderer);
	void shutdown();

private:
	void update();
	void render(SDL_Renderer* renderer);

	void changeState(std::shared_ptr<state::GameState>& newState, std::unique_ptr<GameObjects>& gameObjects);
	std::shared_ptr<state::GameState>& getState(state::StateType type);

	int m_frameStep{};
	Uint64 m_lastStep = 0;
	std::unique_ptr<GameObjects> m_gameObjects; // remove
	std::shared_ptr<state::GameState> m_state;
	std::unordered_map<state::StateType, std::shared_ptr<state::GameState>> m_states;
};