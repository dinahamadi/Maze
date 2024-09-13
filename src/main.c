#include "../inc/maze.h"
#include <SDL2/SDL.h>


/**
 * main - Entry point for the maze game application.
 * @argc: Number of command-line arguments (unused).
 * @argv: Array of command-line argument strings (unused).
 *
 * Return: 0 on success, -1 on failure.
 */
int main(int argc, char *argv[])
{
	int running;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	GameState state;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (-1);
	}
	if (initialize(&window, &renderer, &state) != 0)
	{
		return (-1);
	}
	if (loadTextures(renderer, &state) != 0)
	{
		cleanUp(window, renderer, &state);
		return (-1);
	}
	if (loadMap(argv[1], &state) != 0)
	{
		cleanUp(window, renderer, &state);
		return (-1);
	}
	running = 1;
	while (running)
	{
		SDL_Event event;

		handleEvents(&event, &running, &state);
		updatePlayerPosition(&state);
		handleCollisions(&state);
		renderFrame(renderer, &state);
		SDL_Delay(16);
	}

	cleanUp(window, renderer, &state);
	return (0);
}
