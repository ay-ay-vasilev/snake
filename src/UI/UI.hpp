#pragma once

#include <SDL3_image/SDL_image.h>
#include <string>

#include "../Abstract/Observer.hpp"

struct ImFont;

namespace ui
{
	struct UIText
	{
		int x;
		int y;
		double scale;
		std::string text;
	};

	class UI : public IObserver
	{
	public:
		UI() {}

		void init(SDL_Window* window, SDL_Renderer* renderer);
		void handleInput(void* appstate, SDL_Event* event);
		void update();
		void preRender(SDL_Renderer* renderer);
		void postRender(SDL_Renderer* renderer);
		void shutdown();

		void addScore(int value);
		void setGameStateText(const std::string_view& text);
		void setDebugText(const std::string_view& text);

	private:
		void getNotified(const ObserverMessage& message) override;

		void renderUIText(SDL_Renderer* renderer, const UIText& uiText);

		ImFont* regularFont;

		UIText m_scoreText{};
		UIText m_gameStateText{};
		UIText m_debugText{};
		int m_score{0};
		std::pair<int, int> m_windowSize{};
		std::pair<int, int> m_offset{};
	};
}