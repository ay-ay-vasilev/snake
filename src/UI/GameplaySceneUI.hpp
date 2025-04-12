#pragma once

#include <SDL3_image/SDL_image.h>
#include <string>

#include "UI.hpp"

struct ImFont;

namespace ui
{
	class GameplaySceneUI : public UI
	{
	public:
		GameplaySceneUI() {}
		~GameplaySceneUI() override = default;
		void init(SDL_Window* window, SDL_Renderer* renderer) override;
		void handleInput(void* appstate, SDL_Event* event) override;
		void update() override;
		void preRender(SDL_Renderer* renderer) override;
		void postRender(SDL_Renderer* renderer) override;
		void shutdown() override;

	private:
		void getNotified(const ObserverMessage& message) override;

		void setGameStateText(const std::string_view& text);
		void setDebugText(const std::string_view& text);
		void addScore(int value);
		void clearScore();
		ImFont* regularFont;

		UIText m_scoreText{};
		UIText m_gameStateText{};
		UIText m_debugText{};
		int m_score{0};
	};
}
