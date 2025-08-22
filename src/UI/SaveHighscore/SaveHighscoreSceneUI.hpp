#pragma once

#include "../SceneUI.hpp"

namespace ui
{
class SaveHighscoreSceneUI : public SceneUI
{
public:
	SaveHighscoreSceneUI(GameContextRef gameContext, FontsMapRef fonts) : SceneUI(gameContext, fonts) {}
	~SaveHighscoreSceneUI() override = default;
	void init() override;
	void handleInput(void* appstate, SDL_Event* event) override;
	void update() override;
	void render(SDL_Renderer* renderer, int windowFlags) override;

private:
	void renderTitle();
	void renderScore();

	void getNotified(const ObserverMessage& message) override {}
};
}
