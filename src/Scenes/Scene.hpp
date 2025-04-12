#pragma once

#include <SDL3/SDL.h>
#include <optional>

class SDL_Renderer;

namespace ui
{
	class UI;
}

namespace scene
{
	enum class SceneType
	{
		eMainMenu,
		eOptions,
		eGameplay
	};
	
	class Scene
	{
	public:
		Scene() {};
		virtual ~Scene() = default;
		virtual void init(SDL_Window* window, SDL_Renderer* renderer) = 0;
		virtual void update() = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		virtual void shutdown() = 0;
		virtual std::optional<SceneType> handleInput(void* appstate, SDL_Event* event) = 0;
		virtual void onEnter() = 0;
		virtual void onExit() = 0;
	};
}
