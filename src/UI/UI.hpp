#pragma once

#include <SDL3_image/SDL_image.h>
#include <string>

#include "../Abstract/Observer.hpp"

namespace constants
{
	struct TextData;
}

namespace ui
{
	struct UIText
	{
		int x;
		int y;
		double scale;
		std::string text;
	};

	void initUIText(const constants::TextData& textData, ui::UIText& uiText);

	class UI : public IObserver
	{
	public:
		UI() {}
		virtual ~UI() {}

		virtual void init(SDL_Window* window, SDL_Renderer* renderer);
		virtual void handleInput(void* appstate, SDL_Event* event);
		virtual void update();
		virtual void preRender(SDL_Renderer* renderer);
		virtual void postRender(SDL_Renderer* renderer);
		virtual void shutdown();

	protected:
		void renderUIText(SDL_Renderer* renderer, const UIText& uiText);

		std::pair<int, int> m_windowSize{};
		std::pair<int, int> m_offset{};
	};
}
