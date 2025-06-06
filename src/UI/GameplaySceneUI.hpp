#pragma once

#include "SceneUI.hpp"

namespace ui
{
	class GameplaySceneUI : public SceneUI
	{
	public:
		GameplaySceneUI(GameContextRef gameContext, FontsMapRef fonts) : SceneUI(gameContext, fonts) {}
		~GameplaySceneUI() override = default;
		void init() override;
		void handleInput(void* appstate, SDL_Event* event) override;
		void update() override;
		void render(SDL_Renderer* renderer, int windowFlags) override;

	private:
		void getNotified(const ObserverMessage& message) override;

		void setGameStateText(const std::string_view& text);
		void setDebugText(const std::string_view& text);
		void addScore(int value);
		void clearScore();

		UIText m_scoreText{};
		UIText m_gameStateText{};
		UIText m_debugText{};
		int m_score{0};
		std::pair<int, int> m_offset{};
	};
}
