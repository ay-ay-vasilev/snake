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

namespace data
{
struct TextData;
}

class ImFont;
using FontsMapRef = std::unordered_map<std::string, ImFont*>&;

namespace ui
{
struct UIText // todo: utilize better
{
	int x;
	int y;
	double scale;
	std::string text;
};

void initUIText(const data::TextData& textData, ui::UIText& uiText);

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
	GameContextRef m_gameContext;
	std::pair<int, int> m_windowSize{0, 0};
	std::function<void(UICommand)> m_commandCallback;
	FontsMapRef m_fonts;

	void renderButtons();
	std::vector<UIButton> m_buttons;
	int m_selectedIndex{0};
};
}
