#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* Map dimensions and screen resolution */
#define MAP_WIDTH 16
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* Mouse sensitivity for camera control */
#define MOUSE_SENSITIVITY 0.00001f

/**
 * struct GameState - Holds the state of the game.
 * @screenWidth: The width of the screen.
 * @screenHeight: The height of the screen.
 * @worldMap: 2D array representing the world map.
 * @skyColor: Color of the sky.
 * @wallColor: Color of the walls.
 * @floorColor: Color of the floor.
 * @posX: X-coordinate of the player's position.
 * @posY: Y-coordinate of the player's position.
 * @dirX: X-component of the player's direction.
 * @dirY: Y-component of the player's direction.
 * @planeX: X-component of the camera plane.
 * @planeY: Y-component of the camera plane.
 * @cameraAngle: Current angle of the camera.
 * @rotationSpeed: Speed of camera rotation.
 * @mouseX: X-coordinate of the mouse position.
 * @mouseY: Y-coordinate of the mouse position.
 * @wallTexture: a pointer to the walls texture.
 * @groundTexture: a pointer to the gound texture.
 * @weaponTextures: an array to hold different weapon textures.
 * @currentWeaponIndex: Represent the currently used weapon.
 */
typedef struct GameState
{
	int screenWidth;
	int screenHeight;
	int worldMap[MAP_WIDTH][MAP_HEIGHT];
	SDL_Color skyColor;
	SDL_Color wallColor;
	SDL_Color floorColor;
	float posX;
	float posY;
	float dirX;
	float dirY;
	float planeX;
	float planeY;
	float cameraAngle;
	float rotationSpeed;
	int mouseX;
	int mouseY;
	SDL_Texture *wallTexture;
	SDL_Texture *groundTexture;
	SDL_Texture *weaponTextures[4];
	int currentWeaponIndex;
} GameState;


/* maze.c functions */
int initSDL(SDL_Window **window, SDL_Renderer **renderer);
int initialize(SDL_Window **window, SDL_Renderer **renderer, GameState *state);
int loadMap(const char *filename, GameState *state);
void cleanUp(SDL_Window *window, SDL_Renderer *renderer, GameState *state);

/* events1.c functions */
void handleEvents(SDL_Event *event, int *running, GameState *state);
void handleKeyDownEvent(SDL_Event *event, GameState *state);
void handleMouseMotionEvent(SDL_Event *event, GameState *state);
void rotate(GameState *state, float angle);
void moveForward(GameState *state, float distance);
void strafe(GameState *state, float distance);

/* events2.c functions */
void handleCollisions(GameState *state);
void updatePlayerPosition(GameState *state);
void rotateCamera(GameState *state, float angle);

/* rendering1.c functions */
void renderFrame(SDL_Renderer *renderer, GameState *state);
void renderBackground(SDL_Renderer *renderer, GameState *state);
void drawWalls(SDL_Renderer *renderer, GameState *state);

/* rendering2.c functions */
int performDDA(float rayDirX, float rayDirY, GameState *state,
		int *mapX, int *mapY, float *sideDistX, float *sideDistY,
		int *stepX, int *stepY);
float calculatePerpWallDist(float rayDirX, float rayDirY, GameState *state,
		int mapX, int mapY, int stepX, int stepY, int side);
int loadTextures(SDL_Renderer *renderer, GameState *state);
void renderWeapon(SDL_Renderer *renderer, GameState *state);

#endif
