#pragma once

#include "../SceneUI.hpp"
#include "../../Options/OptionsManager.hpp"

namespace ui
{
class OptionsSceneUI : public SceneUI
{
public:
	OptionsSceneUI(GameContextRef gameContext, FontsMapRef fonts) : SceneUI(gameContext, fonts) {}
	~OptionsSceneUI() override = default;
	void init() override;
	void handleInput(void* appstate, SDL_Event* event) override;
	void update() override;
	void render(SDL_Renderer* renderer, int windowFlags) override;

private:
	void renderTitle();
	void renderResolutionsOption();
	void renderResolutionsTreeNode();
	void renderFullscreenOption();
	void renderSnakeColorOptions();
	// Resolution
	std::unordered_map<std::string, options::Resolution> m_resolutions;
	std::string m_selectedResolutionName;
	bool m_shouldResolutionTreeClose;
	bool m_isResolutionTreeHovered;
	// Fullscreen
	bool m_isFullscreen;
	// Snake colors
	ImVec4 m_snake1Color;
	ImVec4 m_snake2Color;

	void getNotified(const ObserverMessage& message) override {} 
};


}
