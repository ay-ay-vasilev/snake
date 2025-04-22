#pragma once

#include "Scene.hpp"

namespace scene
{
	class OptionsScene : public Scene
	{
		public:
			OptionsScene(GameContextRef gameContext) : Scene(gameContext) {}
			~OptionsScene() override = default;
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
