#include "../inc/maze.h"
/**
 * loadEnemyTextures - Loads the enemy texture from the specified file.
 * @state: Pointer to the GameState structure.
 * @renderer: Pointer to the SDL_Renderer used for rendering.
 * Return: 0 on success, -1 on failure.
 */

int loadEnemyTextures(GameState *state, SDL_Renderer *renderer)
{
	SDL_Surface *enemySurface = IMG_Load("img/enemy.png");

	if (!enemySurface)
	{
		fprintf(stderr, "Failed to load enemy texture: %s\n", IMG_GetError());
		return (-1);
	}
	state->enemyTexture = SDL_CreateTextureFromSurface(renderer, enemySurface);
	SDL_FreeSurface(enemySurface);
	if (!state->enemyTexture)
	{
		fprintf(stderr, "Failed to create enemy texture: %s\n", SDL_GetError());
		return (-1);
	}

	return (0);
}
/**
 * isEnemyVisible - Check if the enemy is visible from the player's position.
 * @state: Pointer to the current game state.
 * @enemyX: The X coordinate of the enemy's position.
 * @enemyY: The Y coordinate of the enemy's position.
 * Return: true if the enemy is visible, false otherwise.
 */
bool isEnemyVisible(GameState *state, float enemyX, float enemyY)
{
	float deltaX, deltaY, distance, step;
	int checkX, checkY;

	deltaX = enemyX - state->posX;
	deltaY = enemyY - state->posY;
	distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	for (step = 0; step < distance; step += 0.1f)
	{
		checkX = (int)(state->posX + (step * (deltaX / distance)));
		checkY = (int)(state->posY + (step * (deltaY / distance)));
		if (checkX < 0 || checkX >= MAP_WIDTH ||
				checkY < 0 || checkY >= MAP_HEIGHT)
			break;
		if (state->worldMap[checkY][checkX] == 1)
			return (false);
	}
	return (true);
}
/**
 * isEnemyVisibleAndClose - Check if the enemy is both visible and within a
 *                          certain distance from the player.
 * @state: Pointer to the current game state.
 * @enemyX: The X coordinate of the enemy's position.
 * @enemyY: The Y coordinate of the enemy's position.
 * Return: 1 if the enemy is visible and close, 0 otherwise.
 */
int isEnemyVisibleAndClose(GameState *state, float enemyX, float enemyY)
{
	float deltaX = enemyX - state->posX;
	float deltaY = enemyY - state->posY;
	float distanceToEnemy = sqrt(deltaX * deltaX + deltaY * deltaY);
	float visibilityThreshold = 4.0f;

	return (distanceToEnemy < visibilityThreshold &&
			isEnemyVisible(state, enemyX, enemyY));
}
/**
 * drawEnemy - Render an enemy sprite on the screen based on the player's
 *             perspective.
 * @renderer: Pointer to the SDL renderer used for rendering the enemy.
 * @state: Pointer to the current game state.
 * @zBuffer: Array containing depth information for the current frame.
 * @enemyX: The X coordinate of the enemy's position.
 * @enemyY: The Y coordinate of the enemy's position.
 */
void drawEnemy(SDL_Renderer *renderer, GameState *state,
		float zBuffer[], float enemyX, float enemyY)
{
	(void)renderer;
	SDL_Rect enemyRect;
	float deltaX, deltaY, invDet, transformX, transformY;
	float angleThreshold, enemyAngle, playerAngle, angleDifference;
	int enemyScreenX, spriteHeight, spriteWidth, drawStartY;
	int drawStartX, drawEndY, drawEndX;

	deltaX = enemyX - state->posX;
	deltaY = enemyY - state->posY;
	invDet = 1.0f / (state->planeX * state->dirY - state->dirX * state->planeY);
	transformX = invDet * (state->dirY * deltaX - state->dirX * deltaY);
	transformY = invDet * (-state->planeY * deltaX + state->planeX * deltaY);
	angleThreshold = M_PI / 8;
	enemyAngle = atan2(deltaY, deltaX);
	playerAngle = atan2(state->dirY, state->dirX);
	angleDifference = fmod((enemyAngle - playerAngle + M_PI), (2 * M_PI)) - M_PI;
	if (transformY > 0 && fabs(angleDifference) < angleThreshold)
	{
		enemyScreenX = (int)((state->screenWidth / 2) *
				(1 + transformX / transformY));
		enemyScreenX = fmax(0, fmin(enemyScreenX, state->screenWidth - 1));
		spriteHeight = (int)(state->screenHeight / transformY * 0.8f);
		spriteWidth = (int)(state->screenHeight / transformY * 0.8f);
		drawStartY = fmax((state->screenHeight / 2) - (spriteHeight / 2), 0);
		drawStartX = fmax(enemyScreenX - spriteWidth / 2, 0);
		drawEndY = fmin(drawStartY + spriteHeight, state->screenHeight - 1);
		drawEndX = fmin(drawStartX + spriteWidth, state->screenWidth - 1);
		if (drawStartX < drawEndX && drawStartY < drawEndY &&
				transformY < zBuffer[enemyScreenX])
		{
			enemyRect.x = drawStartX;
			enemyRect.y = drawStartY;
			enemyRect.w = drawEndX - drawStartX;
			enemyRect.h = drawEndY - drawStartY;
			if (SDL_RenderCopy(renderer, state->enemyTexture,
						NULL, &enemyRect) != 0)
				printf("SDL_RenderCopy error: %s\n", SDL_GetError());
		}
	}
}
/**
 * drawEnemies - Iterate over all enemies in the game world and draw them
 *               if they are visible from the player's position.
 * @renderer: Pointer to the SDL renderer used for rendering enemies.
 * @state: Pointer to the current game state.
 * @zBuffer: Array containing depth information for the current frame.
 */
void drawEnemies(SDL_Renderer *renderer, GameState *state, float zBuffer[])
{
	int i, j;
	float enemyX, enemyY;

	for (i = 0; i < MAP_HEIGHT; i++)
	{
		for (j = 0; j < MAP_WIDTH; j++)
		{
			if (state->worldMap[i][j] == 2)
			{
				enemyX = (float)j + 0.5f;
				enemyY = (float)i + 0.5f;
				if (isEnemyVisibleAndClose(state, enemyX, enemyY))
					drawEnemy(renderer, state, zBuffer, enemyX, enemyY);
			}
		}
	}
}
