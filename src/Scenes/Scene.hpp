#pragma once

#include <SDL3/SDL.h>
#include <optional>
#include <memory>

class SDL_Renderer;

namespace context
{
	class GameContext;
}
using GameContextRef = std::unique_ptr<context::GameContext>&;

namespace ui
{
	class UIManager;
}

namespace scene
{
enum class eSceneType
{
	MainMenu,
	Options,
	Gameplay,
	Highscores
};

class Scene
{
public:
	Scene(GameContextRef gameContext) : m_gameContext(gameContext) {};
	virtual ~Scene() = default;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void shutdown() = 0;
	virtual std::optional<eSceneType> handleInput(void* appstate, SDL_Event* event) = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void setSceneUI(std::unique_ptr<ui::UIManager>& uiManager) = 0;
protected:
	GameContextRef m_gameContext;
};
}
