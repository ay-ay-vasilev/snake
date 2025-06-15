#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <memory>

#include "Game/Game.hpp"
#include "Game/GameContext.hpp"
#include "Options/OptionsManager.hpp"
#include "UI/UIManager.hpp"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

std::unique_ptr<context::GameContext> gameContext;
std::unique_ptr<Game> game;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
	gameContext = std::make_unique<context::GameContext>();
	game = std::make_unique<Game>(gameContext);

	auto& optionsManager = gameContext->getOptionsManager();
	auto currentResolution = optionsManager->getCurrentResolution();
	const auto windowWidth = currentResolution.width;
	const auto windowHeight = currentResolution.height;
	auto isFullscreen = optionsManager->getIsFullscreen();

	/* Create the window */
	SDL_WindowFlags flags = 0;
	if (isFullscreen) flags |= SDL_WINDOW_FULLSCREEN;
	if (!SDL_CreateWindowAndRenderer("Snake Game", windowWidth, windowHeight, flags, &window, &renderer))
	{
		SDL_Log("Couldn't create window and renderer: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	optionsManager->setWindow(window);

	game->init(window, renderer);
	return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	return game->handleInput(appstate, event);
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
	const auto result = game->gameLoop(appstate, renderer);
	return result;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	if (appstate)
	{
		game->shutdown();

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
}
