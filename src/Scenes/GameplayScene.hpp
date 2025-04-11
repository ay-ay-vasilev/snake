#pragma once

#include "Scene.hpp"
#include <memory>
#include <unordered_map>

namespace state
{
	class GameState;
	enum class StateType;
}

namespace scene
{
	class GameplayScene : public Scene
	{
		public:
			~GameplayScene() override = default;
			void init(ui::UI& uiManager) override;
			void update() override;
			void render(SDL_Renderer* renderer) override;
			std::optional<scene::SceneType> handleInput(void *appstate, SDL_Event* event) override;
			void onEnter() override;
			void onExit() override;

		private:
			void changeState(state::StateType newState);

			std::unordered_map<state::StateType, std::shared_ptr<state::GameState>> m_states;
			std::shared_ptr<state::GameState> m_state;
	};
}