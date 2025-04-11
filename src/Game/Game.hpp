#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <unordered_map>

class GameObjects;
class SDL_Renderer;

namespace scene
{
	class Scene;
	enum class SceneType;
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

	void changeScene(scene::SceneType type);

	int m_frameStep{};
	Uint64 m_lastStep = 0;

	std::unordered_map<scene::SceneType, std::shared_ptr<scene::Scene>> m_scenes;
	std::shared_ptr<scene::Scene> m_currentScene;
};