#pragma once

#include "../SceneUI.hpp"

namespace ui
{
class HighscoresSceneUI : public SceneUI
{
public:
	HighscoresSceneUI(GameContextRef gameContext, FontsMapRef fonts) : SceneUI(gameContext, fonts) {}
	~HighscoresSceneUI() override = default;
	void init() override;
	void handleInput(void* appstate, SDL_Event* event) override;
	void update() override;
	void render(SDL_Renderer* renderer, int windowFlags) override;

	void renderTitle();
	void renderHighscoresTable();

private:
	void getNotified(const ObserverMessage& message) override {} 

	std::string m_title{};
};
}
