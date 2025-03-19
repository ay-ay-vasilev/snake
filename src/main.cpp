#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "Game/Game.hpp"
#include "Game/Constants.hpp"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static Game game;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
	auto& dataManager = constants::DataManager::getInstance();
	dataManager.LoadConstants();

	const auto windowWidth = dataManager.getWindowWidth();
	const auto windowHeight = dataManager.getWindowHeight();

	/* Create the window */
	if (!SDL_CreateWindowAndRenderer("Snake Game", windowWidth, windowHeight, 0, &window, &renderer))
	{
		SDL_Log("Couldn't create window and renderer: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	game.init();

	return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	return game.handleInput(appstate, event);
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
	return game.gameLoop(appstate, renderer);
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	if (appstate)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
}