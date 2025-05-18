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
	// Resolution
	std::vector<options::Resolution> m_resolutions;
	int m_selectedResolutionId;

	void getNotified(const ObserverMessage& message) override {} 
};


}
