#pragma once

#include <SDL3_image/SDL_image.h>

#include "../SceneUI.hpp"
#include "MainMenuSceneUIButton.hpp"

#include <vector>

namespace ui
{
	class MainMenuSceneUI : public SceneUI
	{
	public:
		MainMenuSceneUI() {}
		~MainMenuSceneUI() override = default;
		void init() override;
		void handleInput(void* appstate, SDL_Event* event) override;
		void update() override;
		void render(SDL_Renderer* renderer, int windowFlags) override;

	private:
		void getNotified(const ObserverMessage& message) override {} 
		void renderButtons();
		
		std::vector<MainMenuSceneUIButton> m_buttons;
		int m_selectedIndex;
		std::string m_title{};
	};
}
