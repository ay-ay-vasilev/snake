#pragma once

#include "Scene.hpp"

namespace context
{
	class GameContext;
}

namespace scene
{
	class HighscoresScene : public Scene
	{
		public:
			HighscoresScene(GameContextRef gameContext) : Scene(gameContext) {}
			~HighscoresScene() override = default;
			void init() override;
			void setSceneUI(std::unique_ptr<ui::UIManager>& uiManager) override;
			void update() override;
			void render(SDL_Renderer* renderer) override;
			void shutdown() override;
			std::optional<scene::eSceneType> handleInput(void *appstate, SDL_Event* event) override;
			void onEnter() override;
			void onExit() override;
	};
}
