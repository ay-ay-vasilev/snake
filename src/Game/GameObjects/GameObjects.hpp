#pragma once

#include "Grid.hpp"
#include "Snake.hpp"
#include "Food.hpp"

#include <memory>

class SDL_Renderer;
class GameObjects
{
public:
	inline const std::unique_ptr<Grid>& getGrid() { return m_grid; };
	inline const std::unique_ptr<Snake>& getSnake() { return m_snake; };
	inline const std::unique_ptr<Food>& getFood() { return m_food; };

	void reset();
	void init();
	void update();
	void render(SDL_Renderer* renderer);

private:
	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Food> m_food;
};