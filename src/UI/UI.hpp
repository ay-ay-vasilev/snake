#pragma once

#include <SDL3_image/SDL_image.h>

#include "../Abstract/Observer.hpp"
//#include <iostream>

namespace ui
{
	class UI : public IObserver
	{
	public:
		UI()
		{
			//std::cout << "UI created!\n";
		}
		virtual ~UI() {}

		virtual void init() = 0;
		virtual void handleInput(void* appstate, SDL_Event* event) = 0;
		virtual void update() = 0;
		virtual void render(SDL_Renderer* renderer, int windowFlags) = 0;
	};
}
