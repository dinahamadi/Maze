# Maze Project :bricks:

Welcome to the **Maze Project**! This is an innovative maze game built using SDL2 and C, designed to challenge your navigation skills with complex mazes and interactive gameplay.

![Maze Screenshot](maze-screenshot.png)

## Introduction :woman_teacher:

The goal of this project is to create a 3D game using raycasting techniques. Players navigate through a maze by rotating and moving their camera perspective while avoiding collisions with walls. The game includes various weapons, allowing for an engaging gameplay experience.

## Background Context :female_detective:

This project aims to implement a maze game where the player can:
- Rotate the camera using the left and right arrow keys.
- Move within the maze using the W, A, S, and D keys.
- Handle collisions with walls effectively.
- Utilize a map stored in a `map.txt` file to define the maze layout.
- Change weapons by pressing the number keys (1-4), each corresponding to a different weapon.

## Installation :rocket:

Ready to dive into the maze? Follow these steps to get started:

1. Clone the repository:
   ```bash
   git clone https://github.com/dinahamadi/Maze.git
   cd maze

2. Install the required dependencies:
   ```bash
   sudo apt-get install libsdl2-dev

3. Compile the project using:
   ```bash
   gcc -Wall -Werror -Wextra -pedantic -o maze src/*.c -lSDL2 -lSDL2_image -lm

## Usage :computer_mouse:
To run the Maze Project, execute the compiled binary:
   ```bash
   ./maze map.txt
   ```
or you can povide your own map file and provide it as an argument

Use the following controls during gameplay:

- Arrow Keys: Rotate the camera.
- Mouse moves: Rotate the camera, just like a FPS game !
- W, A, S, D: Move within the maze.
- Number Keys (1-4): Change the weapon.

## Contributing :hammer_and_wrench:

We welcome contributions to the Maze Project! To get started, please follow these steps:

1. **Fork the Repository**: Click the "Fork" button at the top right of the Maze Project GitHub page to create your own copy of the repository.
2. **Clone Your Fork**:
   ```bash
   git clone https://github.com/yourusername/Maze.git
   cd Maze

3. **Create a New Branch**: It's a good practice to create a new branch for your feature or bug fix.
   ```bash
   git checkout -b feature/YourFeatureName

4. **Make Your Changes**: Implement your feature or fix a bug. Ensure that your code adheres to the project's coding standards.
5. **Commit Your Changes**: Commit your changes with a clear and concise commit message.
   ```bash
   git add .
   git commit -m "Add your message here"

6. **Push to Your Branch**: Push your changes to your forked repository.
```bash
   git push origin feature/YourFeatureName
```

7. **Create a Pull Request**: Go to the original Maze Project repository, and click on the "Pull Requests" tab. Click "New Pull Request," select your branch, and submit your request.

Follow Up: After submitting your pull request, be available for any discussions or feedback from the maintainers.

Thank you for contributing to the Maze Project! Your help is greatly appreciated.
## Authors :bowtie:

- **Dina Hammadi** <[dinahamadi](https://github.com/dinahamadi)>

## Licensing :receipt:

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Thank you for checking out the Maze Project! We hope you enjoy navigating through the maze!