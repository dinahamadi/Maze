#include "../inc/maze.h"

/**
 * renderFrame - Renders a frame of the raycasting game.
 * @renderer: Pointer to the SDL_Renderer used for rendering.
 * @state: Pointer to the GameState structure.
 */
void renderFrame(SDL_Renderer *renderer, GameState *state)
{
	renderBackground(renderer, state);
	renderWeapon(renderer, state);
	drawWalls(renderer, state);
	renderWeapon(renderer, state);
	SDL_RenderPresent(renderer);
}
/**
 * renderBackground - Clears the screen with the sky color and draws the floor.
 * @renderer: Pointer to the SDL_Renderer used for rendering.
 * @state: Pointer to the GameState structure.
 */
void renderBackground(SDL_Renderer *renderer, GameState *state)
{
	SDL_Rect rect;

	SDL_SetRenderDrawColor(renderer, state->skyColor.r, state->skyColor.g,
			state->skyColor.b, state->skyColor.a);
	SDL_RenderClear(renderer);

	rect.x = 0;
	rect.y = state->screenHeight / 2;
	rect.w = state->screenWidth;
	rect.h = state->screenHeight / 2;
	SDL_RenderCopy(renderer, state->groundTexture, NULL, &rect);
}
/**
 * drawWalls - Uses raycasting to draw walls on the screen.
 * @renderer: Pointer to the SDL_Renderer used for rendering.
 * @state: Pointer to the GameState structure.
 */
void drawWalls(SDL_Renderer *renderer, GameState *state)
{
	int x, mapX, mapY, stepX, stepY, side;
	int texWidth = 124, texHeight = 124;
	float cameraX, rayDirX, rayDirY;
	float sideDistX, sideDistY, perpWallDist, wallX;
	int lineHeight, drawStart, drawEnd, texX;
	SDL_Rect wallRect, textureRect;

	for (x = 0; x < state->screenWidth; x++)
	{
		cameraX = 2 * x / (float)state->screenWidth - 1;
		rayDirX = state->dirX + state->planeX * cameraX;
		rayDirY = state->dirY + state->planeY * cameraX;
		mapX = (int)state->posX;
		mapY = (int)state->posY;
		sideDistX = (rayDirX < 0) ?
			(state->posX - mapX) * fabsf(1 / rayDirX) :
			(mapX + 1.0 - state->posX) * fabsf(1 / rayDirX);
		sideDistY = (rayDirY < 0) ?
			(state->posY - mapY) * fabsf(1 / rayDirY) :
			(mapY + 1.0 - state->posY) * fabsf(1 / rayDirY);
		stepX = (rayDirX < 0) ? -1 : 1;
		stepY = (rayDirY < 0) ? -1 : 1;
		side = performDDA(rayDirX, rayDirY, state, &mapX, &mapY,
				&sideDistX, &sideDistY, &stepX, &stepY);
		perpWallDist = calculatePerpWallDist(rayDirX, rayDirY, state,
				mapX, mapY, stepX, stepY, side);
		lineHeight = (int)(state->screenHeight / perpWallDist);
		drawStart = -lineHeight / 2 + state->screenHeight / 2;
		drawEnd = lineHeight / 2 + state->screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= state->screenHeight)
			drawEnd = state->screenHeight - 1;
		if (side == 0)
			wallX = state->posY + perpWallDist * rayDirY;
		else
			wallX = state->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		texX = (int)(wallX * (float)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;
		wallRect.x = x;
		wallRect.y = drawStart;
		wallRect.w = 1;
		wallRect.h = drawEnd - drawStart;
		textureRect = {texX, 0, 1, texHeight};
		SDL_RenderCopy(renderer, state->wallTexture, &textureRect, &wallRect);
	}
}


/**
 * calculateStepAndSideDist - Calculates the step&side distances for raycasting
 * @rayDirX: The X direction of the ray.
 * @rayDirY: The Y direction of the ray.
 * @state: Pointer to the GameState structure.
 * @mapX: The current map X coordinate.
 * @mapY: The current map Y coordinate.
 * @stepX: Pointer to the step X value to be calculated.
 * @stepY: Pointer to the step Y value to be calculated.
 * @sideDistX: Pointer to the side distance X value to be calculated.
 * @sideDistY: Pointer to the side distance Y value to be calculated.
 */
void calculateStepAndSideDist(float rayDirX, float rayDirY, GameState *state,
		int mapX, int mapY, int *stepX, int *stepY,
		float *sideDistX, float *sideDistY)
{
	if (rayDirX < 0)
	{
		*stepX = -1;
		*sideDistX = (state->posX - mapX) * fabsf(1 / rayDirX);
	}
	else
	{
		*stepX = 1;
		*sideDistX = (mapX + 1.0 - state->posX) * fabsf(1 / rayDirX);
	}

	if (rayDirY < 0)
	{
		*stepY = -1;
		*sideDistY = (state->posY - mapY) * fabsf(1 / rayDirY);
	}
	else
	{
		*stepY = 1;
		*sideDistY = (mapY + 1.0 - state->posY) * fabsf(1 / rayDirY);
	}
}
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


