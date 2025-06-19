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
	void renderResolutionsOptions();
	void renderResolutionsTreeNode();
	void renderFullscreenOption();
	void renderSnakeColorOptions();
	void renderGameSpeedOptions();
	void renderGameSpeedTreeNode();
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
	// Game speed
	std::vector<std::string> m_gameSpeedPresets;
	std::string m_selectedGameSpeed;
	bool m_shouldGameSpeedTreeClose;
	bool m_isGameSpeedTreeHovered;

	void getNotified(const ObserverMessage& message) override {} 
};


}
