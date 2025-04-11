#pragma once

#include "Scene.hpp"

namespace scene
{
	class MainMenuScene : public Scene
	{
		public:
			~MainMenuScene() override = default;
			void init(ui::UI& uiManager) override;
			void update() override;
			void render(SDL_Renderer* renderer) override;
			std::optional<scene::SceneType> handleInput(void *appstate, SDL_Event* event) override;
			void onEnter() override;
			void onExit() override;
	};
}