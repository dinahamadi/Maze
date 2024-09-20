# Maze Project

Welcome to the **Maze Project**! This is an innovative maze game built using SDL2 and C, designed to challenge your navigation skills with complex mazes and interactive gameplay.

![Maze Screenshot](maze-screenshot.png)

## Introduction

The goal of this project is to create a 3D game using raycasting techniques. Players navigate through a maze by rotating and moving their camera perspective while avoiding collisions with walls. The game includes various weapons, allowing for an engaging gameplay experience.

## Background Context

This project aims to implement a maze game where the player can:
- Rotate the camera using the left and right arrow keys.
- Move within the maze using the W, A, S, and D keys.
- Handle collisions with walls effectively.
- Utilize a map stored in a `map.txt` file to define the maze layout.
- Change weapons by pressing the number keys (1-4), each corresponding to a different weapon.

## Installation

Ready to dive into the maze? Follow these steps to get started:

1. Clone the repository:
   ```bash
   git clone https://github.com/dinahamadi/Maze.git
   cd maze
2. Install the required dependencies:
   sudo apt-get install libsdl2-dev
3. Compile the project using:
   gcc -Wall -Werror -Wextra -pedantic -o maze src/*.c -lSDL2 -lSDL2_image -lm

## Usage
To run the Maze Project, execute the compiled binary:
   ./maze

Use the following controls during gameplay:

- Arrow Keys: Rotate the camera.
- Mouse moves: Rotate the camera, just like a FPS game !
- W, A, S, D: Move within the maze.
- Number Keys (1-4): Change the weapon.

## Thank you for checking out the Maze Project! We hope you enjoy navigating through the maze!