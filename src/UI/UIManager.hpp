#pragma once

#include "UICommand.hpp"

#include <unordered_map>
#include <string>
#include <optional>
#include <queue>
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

struct ImFont;

namespace context
{
	class GameContext;
}
using GameContextRef = std::unique_ptr<context::GameContext>&;

namespace ui
{

class SceneUI;

class UIManager
{
public:
	UIManager(GameContextRef gameContext) : m_gameContext(gameContext) {}
	void init(SDL_Window* window, SDL_Renderer* renderer);
	void handleInput(void* appstate, SDL_Event* event);
	void update();
	void preRender(SDL_Renderer* renderer);
	void postRender(SDL_Renderer* renderer);
	void shutdown();

	void setSceneUI(std::shared_ptr<SceneUI> sceneUI);

	void pushCommand(const UICommand& command);
	std::optional<UICommand> pollCommand();

	std::unordered_map<std::string, ImFont*>& getFontsRef() { return m_fonts; }
private:
	GameContextRef m_gameContext;

	std::shared_ptr<SceneUI> m_sceneUI;

	std::queue<UICommand> m_commandQueue;
	std::unordered_map<std::string, ImFont*> m_fonts;
};
}
