#pragma once

#include <memory>

class Grid;
class Snake;
class UI;

struct GameObjects
{
	std::unique_ptr<Grid> grid;
	std::unique_ptr<Snake> snake;
	std::unique_ptr<UI> ui;
};