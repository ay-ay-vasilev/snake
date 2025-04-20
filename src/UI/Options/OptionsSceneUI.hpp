#pragma once

#include "../SceneUI.hpp"

namespace ui
{
class OptionsSceneUI : public SceneUI
{
public:
	OptionsSceneUI() {}
	~OptionsSceneUI() override = default;
	void init() override;
	void handleInput(void* appstate, SDL_Event* event) override;
	void update() override;
	void render(SDL_Renderer* renderer, int windowFlags) override;

private:
	void getNotified(const ObserverMessage& message) override {} 
};


}
