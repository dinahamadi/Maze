#include "../inc/maze.h"

/**
 * initSDL - Initializes the SDL environment and creates a window and renderer.
 * @window: Double pointer to the SDL window to be created.
 * @renderer: Double pointer to the SDL renderer to be created.
 *
 * Return: 0 on success, -1 on failure.
 */
int initSDL(SDL_Window **window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
		return (-1);
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		fprintf(stderr, "SDL_image could not initialize! IMG_Error: %s\n",
				IMG_GetError());
		return (-1);
	}
	*window = SDL_CreateWindow("3D maze", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (*window == NULL)
	{
		fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
		return (-1);
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == NULL)
	{
		fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(*window);
		return (-1);
	}

	return (0);
}

/**
 * initialize - Sets up the SDL environment, initializes game state,
 * and copies the world map into the game state.
 * @window: Double pointer to the SDL window to be created and initialized.
 * @renderer: Double pointer to the SDL renderer to be created and initialized.
 * @state: Pointer to the GameState structure to be initialized.
 *
 * Return: 0 on success, -1 on failure.
 */
int initialize(SDL_Window **window, SDL_Renderer **renderer, GameState *state)
{
	if (initSDL(window, renderer) != 0)
		return (-1);
	state->screenWidth = SCREEN_WIDTH;
	state->screenHeight = SCREEN_HEIGHT;
	state->skyColor = (SDL_Color)
	{135, 206, 235, 255};
	state->wallColor = (SDL_Color)
	{192, 192, 192, 255};
	state->floorColor = (SDL_Color)
	{34, 139, 34, 255};
	state->posX = 5.9;
	state->posY = 5.0;
	state->dirX = 0.88;
	state->dirY = 0.47;
	state->planeX = 0.0;
	state->planeY = 0.66;
	state->rotationSpeed = 0.05;
	state->mouseX = SCREEN_WIDTH / 2;
	state->mouseY = SCREEN_HEIGHT / 2;
	state->currentWeaponIndex = 0;
	return (0);
}
/**
 * loadMap - Load the map from a file and store it in the GameState structure.
 * @filename: Path to the map file.
 * @state: Pointer to the GameState structure.
 *
 * Return: 0 on success, -1 on failure.
 */
int loadMap(const char *filename, GameState *state)
{
	FILE *file;
	int i, j;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		perror("Failed to open map file");
		return (-1);
	}
	for (i = 0; i < MAP_HEIGHT; i++)
	{
		for (j = 0; j < MAP_WIDTH; j++)
		{
			if (fscanf(file, "%d", &state->worldMap[j][i]) != 1)
			{
				fprintf(stderr, "Error reading map data.\n");
				fclose(file);
				return (-1);
			}
		}
	}
	fclose(file);
	return (0);
}
/**
 * cleanUp - Cleans up SDL resources by destroying renderer and window.
 * @window: SDL window to be destroyed.
 * @renderer: SDL renderer to be destroyed.
 * @state: Pointer to the GameState structure.
 *
 * Return: void.
 */
void cleanUp(SDL_Window *window, SDL_Renderer *renderer, GameState *state)
{
	if (state->wallTexture != NULL)
		SDL_DestroyTexture(state->wallTexture);
	if (state->groundTexture != NULL)
		SDL_DestroyTexture(state->groundTexture);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}

