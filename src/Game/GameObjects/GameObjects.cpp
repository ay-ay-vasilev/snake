#include "GameObjects.hpp"

#include <SDL3_image/SDL_image.h>

void GameObjects::reset()
{
	m_grid.reset();
	m_snake.reset();
	m_food.reset();
}

void GameObjects::init()
{
	m_grid = std::make_unique<Grid>();
	m_snake = std::make_unique<Snake>(m_gameContext);
	m_food = std::make_unique<Food>();
}

void GameObjects::update()
{
	m_grid->update();
	m_snake->update();
	m_food->update();
}

void GameObjects::render(SDL_Renderer* renderer)
{
	m_grid->render(renderer);
	m_snake->render(renderer);
	m_food->render(renderer);
}
