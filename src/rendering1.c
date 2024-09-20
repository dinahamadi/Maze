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
	float cameraX, rayDirX, rayDirY, sideDistX, sideDistY;
	float perpWallDist, wallX;
	int lineHeight, drawStart, drawEnd, texX;
	SDL_Rect wallRect, textureRect;

	for (x = 0; x < state->screenWidth; x++)
	{
		cameraX = 2 * x / (float)state->screenWidth - 1;
		rayDirX = state->dirX + state->planeX * cameraX;
		rayDirY = state->dirY + state->planeY * cameraX;
		mapX = (int)state->posX;
		mapY = (int)state->posY;

		sideDistX = (rayDirX < 0) ? (state->posX - mapX) * fabsf(1 / rayDirX) :
			(mapX + 1.0 - state->posX) * fabsf(1 / rayDirX);
		sideDistY = (rayDirY < 0) ? (state->posY - mapY) * fabsf(1 / rayDirY) :
			(mapY + 1.0 - state->posY) * fabsf(1 / rayDirY);
		stepX = (rayDirX < 0) ? -1 : 1;
		stepY = (rayDirY < 0) ? -1 : 1;
		side = performDDA(rayDirX, rayDirY, state, &mapX, &mapY,
				&sideDistX, &sideDistY, &stepX, &stepY);
		perpWallDist = calculatePerpWallDist(rayDirX, rayDirY, state,
				mapX, mapY, stepX, stepY, side);
		lineHeight = (int)(state->screenHeight / perpWallDist);
		drawStart = fmax(-lineHeight / 2 + state->screenHeight / 2, 0);
		drawEnd = fmin(lineHeight / 2 + state->screenHeight / 2,
				state->screenHeight - 1);
		wallX = (side == 0) ? state->posY + perpWallDist * rayDirY :
			state->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		texX = (int)(wallX * (float)texWidth);
		if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
			texX = texWidth - texX - 1;
		wallRect = (SDL_Rect){x, drawStart, 1, drawEnd - drawStart};
		textureRect = (SDL_Rect){texX, 0, 1, texHeight};
		SDL_RenderCopy(renderer, state->wallTexture, &textureRect, &wallRect);
	}
}
