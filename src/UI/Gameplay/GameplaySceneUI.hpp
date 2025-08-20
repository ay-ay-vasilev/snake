#pragma once

#include "../SceneUI.hpp"

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

		void addScore(int value);
		void clearScore();

		void renderPause();
		void renderLose();

		UIText m_scoreText{};
		int m_score{0};
		std::pair<int, int> m_offset{};

		bool m_isPaused{};
		bool m_isLose{};
	};
}
