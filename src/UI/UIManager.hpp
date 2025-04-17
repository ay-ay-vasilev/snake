#pragma once

#include "UICommand.hpp"

#include <SDL3_image/SDL_image.h>
#include <optional>
#include <queue>
#include <memory>

struct ImFont;

namespace ui
{

class SceneUI;
struct SceneUIData;

class UIManager
{
public:
	UIManager() {}
	void init(SDL_Window* window, SDL_Renderer* renderer);
	void handleInput(void* appstate, SDL_Event* event);
	void update();
	void preRender(SDL_Renderer* renderer);
	void postRender(SDL_Renderer* renderer);
	void shutdown();

	void setSceneUI(std::shared_ptr<SceneUI> sceneUI);

	void pushCommand(const UICommand& command);
	std::optional<UICommand> pollCommand();
private:
	std::shared_ptr<SceneUI> m_sceneUI;
	std::shared_ptr<SceneUIData> m_sceneUIData;

	std::queue<UICommand> m_commandQueue;
};
}
