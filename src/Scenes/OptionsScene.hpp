#pragma once

#include "Scene.hpp"

namespace scene
{
	class OptionsScene : public Scene
	{
		public:
			~OptionsScene() override = default;
			void init(SDL_Window* window, SDL_Renderer* renderer) override;
			void update() override;
			void render(SDL_Renderer* renderer) override;
			void shutdown() override;
			std::optional<scene::SceneType> handleInput(void *appstate, SDL_Event* event) override;
			void onEnter() override;
			void onExit() override;
	};
}
