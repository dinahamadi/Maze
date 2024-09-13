#include "../inc/maze.h"

/**
 * rotateCamera - Rotates the camera view by a given angle.
 * @state: Pointer to the GameState structure containing direction
 * and plane vectors.
 * @angle: The angle by which the camera should be rotated.
 *
 * Return: void.
 */
void rotateCamera(GameState *state, float angle)
{
	float oldDirX = state->dirX;
	float oldPlaneX = state->planeX;

	state->dirX = state->dirX * cosf(angle) - state->dirY * sinf(angle);
	state->dirY = oldDirX * sinf(angle) + state->dirY * cosf(angle);

	state->planeX = state->planeX * cosf(angle) - state->planeY * sinf(angle);
	state->planeY = oldPlaneX * sinf(angle) + state->planeY * cosf(angle);
}
/**
 * updatePlayerPosition - Updates the player's position based on keyboard.
 * @state: Pointer to the GameState structure.
 */
void updatePlayerPosition(GameState *state)
{
	const Uint8 *stateKeys = SDL_GetKeyboardState(NULL);
	float moveX = 0.0f;
	float moveY = 0.0f;

	if (stateKeys[SDL_SCANCODE_W])
	{
		moveX = state->dirX * MOUSE_SENSITIVITY;
		moveY = state->dirY * MOUSE_SENSITIVITY;
	}
	if (stateKeys[SDL_SCANCODE_S])
	{
		moveX = -state->dirX * MOUSE_SENSITIVITY;
		moveY = -state->dirY * MOUSE_SENSITIVITY;
	}
	if (stateKeys[SDL_SCANCODE_A])
	{
		moveX = -state->dirY * MOUSE_SENSITIVITY;
		moveY = state->dirX * MOUSE_SENSITIVITY;
	}
	if (stateKeys[SDL_SCANCODE_D])
	{
		moveX = state->dirY * MOUSE_SENSITIVITY;
		moveY = -state->dirX * MOUSE_SENSITIVITY;
	}
	state->posX += moveX;
	state->posY += moveY;
}
/**
 * handleCollisions - Checks and handles collisions with walls.
 * @state: Pointer to the GameState structure.
 */
void handleCollisions(GameState *state)
{
	if (state->worldMap[(int)(state->posX + state->dirX * MOUSE_SENSITIVITY)]
			[(int)state->posY] == 1)
		state->posX -= state->dirX * MOUSE_SENSITIVITY;
	if (state->worldMap[(int)state->posX][(int)(state->posY +
				state->dirY * MOUSE_SENSITIVITY)] == 1)
		state->posY -= state->dirY * MOUSE_SENSITIVITY;
}

