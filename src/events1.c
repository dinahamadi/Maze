#include "../inc/maze.h"

/**
 * handleEvents - Handles user input events.
 * @event: Pointer to the SDL event to be handled.
 * @running: Pointer to the running flag of the application.
 * @state: Pointer to the current game state.
 */
void handleEvents(SDL_Event *event, int *running, GameState *state)
{
	while (SDL_PollEvent(event))
	{
		switch (event->type)
		{
			case SDL_QUIT:
				*running = 0;
				break;
			case SDL_WINDOWEVENT:
				if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					state->screenWidth = event->window.data1;
					state->screenHeight = event->window.data2;
				}
				break;
			case SDL_KEYDOWN:
				handleKeyDownEvent(event, state);
				break;
			case SDL_MOUSEMOTION:
				handleMouseMotionEvent(event, state);
				break;
		}
	}
}

/**
 * handleKeyDownEvent - Handles SDL_KEYDOWN events.
 * @event: Pointer to the SDL event to be handled.
 * @state: Pointer to the current game state.
 */
void handleKeyDownEvent(SDL_Event *event, GameState *state)
{
	switch (event->key.keysym.sym)
	{
		case SDLK_LEFT:
			rotateCamera(state, state->rotationSpeed);
			break;
		case SDLK_RIGHT:
			rotateCamera(state, -state->rotationSpeed);
			break;
		case SDLK_w:
			moveForward(state, 0.1);
			break;
		case SDLK_s:
			moveForward(state, -0.1);
			break;
		case SDLK_a:
			strafe(state, -0.1);
			break;
		case SDLK_d:
			strafe(state, 0.1);
			break;
		case SDLK_1:
		case SDLK_KP_1:
			state->currentWeaponIndex = 0;
			break;
		case SDLK_2:
		case SDLK_KP_2:
			state->currentWeaponIndex = 1;
			break;
		case SDLK_3:
		case SDLK_KP_3:
			state->currentWeaponIndex = 2;
			break;
		case SDLK_4:
		case SDLK_KP_4:
			state->currentWeaponIndex = 3;
			break;
	}
}
/**
 * handleMouseMotionEvent - Handles SDL_MOUSEMOTION events.
 * @event: Pointer to the SDL event to be handled.
 * @state: Pointer to the current game state.
 */
void handleMouseMotionEvent(SDL_Event *event, GameState *state)
{
	int deltaX;
	float angle;

	if (state->screenWidth > 0 && state->screenHeight > 0 &&
			event->motion.x >= 0 && event->motion.x < state->screenWidth &&
			event->motion.y >= 0 && event->motion.y < state->screenHeight)
	{
		deltaX = event->motion.xrel;
		if (deltaX != 0)
		{
			angle = deltaX * MOUSE_SENSITIVITY;
			rotateCamera(state, angle);
		}
	}
}

/**
 * moveForward - Moves the player forward or backward.
 * @state: Pointer to the current game state.
 * @distance: The distance to move.
 */
void moveForward(GameState *state, float distance)
{
	state->posX += state->dirX * distance;
	state->posY += state->dirY * distance;
}

/**
 * strafe - Strafes the player left or right.
 * @state: Pointer to the current game state.
 * @distance: The distance to strafe.
 */
void strafe(GameState *state, float distance)
{
	state->posX += state->dirY * distance;
	state->posY -= state->dirX * distance;
}

