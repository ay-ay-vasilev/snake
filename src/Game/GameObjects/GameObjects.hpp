#pragma once

#include "Grid.hpp"
#include "Snake.hpp"
#include "Food.hpp"

#include <memory>

namespace context
{
	class GameContext;
}
using GameContextRef = std::unique_ptr<context::GameContext>&;

class SDL_Renderer;
class GameObjects
{
public:
	GameObjects(GameContextRef gameContext) : m_gameContext(gameContext) {}
	inline const std::unique_ptr<Grid>& getGrid() { return m_grid; };
	inline const std::unique_ptr<Snake>& getSnake() { return m_snake; };
	inline const std::unique_ptr<Food>& getFood() { return m_food; };

	void reset();
	void init();
	void update();
	void render(SDL_Renderer* renderer);

private:
	GameContextRef m_gameContext;
	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Food> m_food;
};
