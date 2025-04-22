#pragma once

#include "Scene.hpp"

#include <memory>
#include <unordered_map>

namespace state
{
	class GameState;
	enum class StateType;
}

namespace ui
{
	class UIManager;
	class GameplaySceneUI;
}

namespace scene
{
class GameplayScene : public Scene
{
public:
	GameplayScene(GameContextRef gameContext) : Scene(gameContext) {}
	~GameplayScene() override = default;
	void init() override;
	void setSceneUI(std::unique_ptr<ui::UIManager>& uiManager) override;
	void update() override;
	void render(SDL_Renderer* renderer) override;
	void shutdown() override;
	std::optional<scene::eSceneType> handleInput(void *appstate, SDL_Event* event) override;
	void onEnter() override;
	void onExit() override;

private:
	void changeState(state::StateType newState);

	std::unordered_map<state::StateType, std::shared_ptr<state::GameState>> m_states;
	std::shared_ptr<state::GameState> m_state;
};
}
