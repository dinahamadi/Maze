#include "../inc/maze.h"
/**
 * performDDA - Performs the Digital Differential Analyzer
 * to find the wall hit.
 * @rayDirX: The X direction of the ray.
 * @rayDirY: The Y direction of the ray.
 * @state: Pointer to the GameState structure.
 * @mapX: Pointer to the current map X coordinate.
 * @mapY: Pointer to the current map Y coordinate.
 * @sideDistX: Pointer to the side distance X value.
 * @sideDistY: Pointer to the side distance Y value.
 * @stepX: Pointer to the step value for the X direction.
 * @stepY: Pointer to the step value for the Y direction.
 * Return: 1 if a wall is hit, 0 otherwise.
 */
int performDDA(float rayDirX, float rayDirY, GameState *state,
		int *mapX, int *mapY, float *sideDistX, float *sideDistY,
		int *stepX, int *stepY)
{
	int hit = 0;
	int side = 0;

	while (hit == 0)
	{
		if (*sideDistX < *sideDistY)
		{
			*sideDistX += fabsf(1 / rayDirX);
			*mapX += *stepX;
			side = 0;
		}
		else
		{
			*sideDistY += fabsf(1 / rayDirY);
			*mapY += *stepY;
			side = 1;
		}
		if (state->worldMap[*mapX][*mapY] > 0)
		{
			hit = 1;
		}
	}
	return (side);
}
/**
 * calculatePerpWallDist - Calculates the perpendicular
 * distance to the wall hit.
 * @rayDirWThe Wof the ray.
 * @rayDirX: The X direction of the ray.
 * @rayDirY: The Y direction of the ray.
 * @state: Pointer to the GameState structure.
 * @mapX: The map X coordinate where the wall was hit.
 * @mapY: The map Y coordinate where the wall was hit.
 * @stepX: The step value in the X direction.
 * @stepY: The step value in the Y direction.
 * @side: The side of the wall hit (0 for X-axis, 1 for Y-axis).
 * Return: The perpendicular distance to the wall.
 */
float calculatePerpWallDist(float rayDirX, float rayDirY, GameState *state,
		int mapX, int mapY, int stepX, int stepY, int side)
{
	float perpWallDist;

	if (side == 0)
	{
		perpWallDist = (mapX - state->posX + (1 - stepX) / 2) / rayDirX;
	}
	else
	{
		perpWallDist = (mapY - state->posY + (1 - stepY) / 2) / rayDirY;
	}
	return (perpWallDist);
}
/**
 * loadTextures - Loads textures for walls, ground, and weapons.
 * @renderer: Pointer to the SDL_Renderer used for rendering.
 * @state: Pointer to the GameState structure.
 *
 * Return: 0 on success, or -1 if any texture fails to load.
 */

int loadTextures(SDL_Renderer *renderer, GameState *state)
{
	int i;
	SDL_Surface *surface;
	const char *weaponFiles[] = {"img/knife.png", "img/pistol.png",
		"img/rifle.png", "img/inf_gun.png"};

	surface = IMG_Load("img/walls.png");
	if (surface == NULL)
	{
		fprintf(stderr, "Failed to load wall texture: %s\n", IMG_GetError());
		return (-1);
	}
	state->wallTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (state->wallTexture == NULL)
		return (-1);
	surface = IMG_Load("img/ground.png");
	if (surface == NULL)
	{
		fprintf(stderr, "Failed to load ground texture: %s\n", IMG_GetError());
		return (-1);
	}
	state->groundTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (state->groundTexture == NULL)
		return (-1);
	for (i = 0; i < 4; i++)
	{
		surface = IMG_Load(weaponFiles[i]);
		if (surface == NULL)
		{
			fprintf(stderr, "Failed to load weapon texture %d\n", i + 1);
			return (-1);
		}
		state->weaponTextures[i] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (state->weaponTextures[i] == NULL)
			return (-1);
	}
	return (0);
}

/**
 * renderWeapon - Renders the current weapon texture to the screen.
 * @renderer: Pointer to the SDL_Renderer used for rendering.
 * @state: Pointer to the GameState structure.
 */
void renderWeapon(SDL_Renderer *renderer, GameState *state)
{
	SDL_Rect weaponRect;
	float weaponWidthPercentage = 0.33f;
	float weaponHeightPercentage = 0.33f;

	weaponRect.w = state->screenWidth * weaponWidthPercentage;
	weaponRect.h = state->screenHeight * weaponHeightPercentage;
	weaponRect.x = (state->screenWidth - weaponRect.w) / 2;
	weaponRect.y = state->screenHeight - weaponRect.h;

	SDL_RenderCopy(renderer, state->weaponTextures[state->currentWeaponIndex],
			NULL, &weaponRect);
}

