#pragma once

#include "../Abstract/Observer.hpp"
#include "UICommand.hpp"
#include "Common/UIButton.hpp"
#include <string>
#include <functional>
#include <memory>

struct SDL_Renderer;
union SDL_Event;

namespace context
{
class GameContext;
}
using GameContextRef = std::unique_ptr<context::GameContext>&;

namespace options
{
class OptionsManager;
struct Resolution;
}

namespace data
{
struct TextData;
}

class ImFont;
using FontsMapRef = std::unordered_map<std::string, ImFont*>&;

namespace ui
{
class SceneUI : public IObserver 
{
public:
	SceneUI(GameContextRef gameContext, FontsMapRef fonts) : m_gameContext(gameContext), m_fonts(fonts) {}
	virtual ~SceneUI() {}

	virtual void init() = 0;
	virtual void handleInput(void* appstate, SDL_Event* event) = 0;
	virtual void update() = 0;
	virtual void render(SDL_Renderer* renderer, int windowFlags) = 0;
	void setCommandCallback(std::function<void(UICommand)> callback);
protected:
	void renderButtons();

	GameContextRef m_gameContext;
	std::function<void(UICommand)> m_commandCallback;
	FontsMapRef m_fonts;

	std::vector<UIButton> m_buttons;
	int m_selectedIndex{0};
	bool m_isSelectionBusy{false};
private:
	void handleInput();

	enum class eInputSource
	{
		Keyboard,
		Mouse
	};
	eInputSource m_lastInput {eInputSource::Keyboard};
};
}
