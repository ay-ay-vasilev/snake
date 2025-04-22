#pragma once

#include "Scene.hpp"

namespace context
{
	class GameContext;
}

namespace scene
{
	class MainMenuScene : public Scene
	{
		public:
			MainMenuScene(GameContextRef gameContext) : Scene(gameContext) {}
			~MainMenuScene() override = default;
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
