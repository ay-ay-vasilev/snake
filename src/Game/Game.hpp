#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <unordered_map>
#include <optional>

class GameObjects;
class SDL_Renderer;

namespace context
{
	class GameContext;
}
using GameContextRef = std::unique_ptr<context::GameContext>&;

namespace scene
{
	class Scene;
	enum class eSceneType;
}

namespace ui
{
	class UIManager;
}

class Game
{
public:
	Game(GameContextRef gameContext) : m_gameContext(gameContext) {}
	~Game();

	void init(SDL_Window* window, SDL_Renderer* renderer);
	SDL_AppResult handleInput(void* appstate, SDL_Event* event);
	SDL_AppResult gameLoop(void* appstate, SDL_Renderer* renderer);
	void shutdown();

private:
	std::optional<SDL_AppResult> update();
	void render(SDL_Renderer* renderer);

	void changeScene(scene::eSceneType type);

	int m_frameStep{};
	Uint64 m_lastStep = 0;

	std::unordered_map<scene::eSceneType, std::shared_ptr<scene::Scene>> m_scenes;
	std::shared_ptr<scene::Scene> m_currentScene;
	std::unique_ptr<ui::UIManager> m_uiManager;
	GameContextRef m_gameContext;
};
