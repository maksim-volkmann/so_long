# Info

strerror - 


# So_Long Project Plan

This plan is designed to guide you through the development of the `so_long` project, ensuring that all requirements are met systematically.

## Initial Setup

- [ ] Review the `so_long` project requirements thoroughly.
- [ ] Clone the [MLX42 library](https://github.com/codam-coding-college/MLX42) or ensure access to the MiniLibX library.
- [ ] Create a project directory structure (src, includes, maps, etc.).

## Makefile Configuration

- [ ] Write a Makefile with rules: `all`, `clean`, `fclean`, `re`.
- [ ] Ensure the Makefile compiles with `-Wall`, `-Wextra`, and `-Werror` flags.
- [ ] Add a rule to compile with the MLX42 library.

## Map Handling

- [ ] Implement function to check for the correct number of arguments.
- [ ] Implement function to validate the map file extension (`.ber`).
- [ ] Implement function to check if the map file exists.
- [ ] Write a function to read the map file and store its content.
- [ ] Validate the map structure (rectangular, surrounded by walls, contains valid symbols).
- [ ] Check for at least one exit, one collectible, and a starting position.
- [ ] Implement error handling for invalid maps.

## Graphic Management

- [ ] Initialize the MLX42/MiniLibX library and create a window.
- [ ] Load textures/sprites (player, walls, collectibles, exit).
- [ ] Implement function to render the map to the window.

## Game Mechanics

- [ ] Implement player movement (W, A, S, D or arrow keys).
- [ ] Prevent movement into walls.
- [ ] Implement collectible pickup logic.
- [ ] Display current number of movements.
- [ ] Implement game win condition (all collectibles picked and player reaches exit).

## Event Handling

- [ ] Handle key press events for player movement.
- [ ] Handle window close event (clicking the cross or pressing ESC).

## Memory Management

- [ ] Ensure all allocated memory is properly freed.
- [ ] Check for memory leaks.

## Testing and Debugging

- [ ] Create test maps of varying complexity and validate the game logic.
- [ ] Use debugging tools to trace and fix bugs.

## Code Refinement

- [ ] Refactor code for readability and efficiency.
- [ ] Add comments and documentation for major functions.

## Submission Preparation

- [ ] Double-check project against the requirements.
- [ ] Prepare a git repository as per submission guidelines.
- [ ] Write a README.md file documenting how to compile and run your game, including any external resources used.

## Bonus Features (If Mandatory Parts Are Perfect)

- [ ] Implement enemy patrols that make the player lose on contact.
- [ ] Add sprite animations for a more dynamic look.
- [ ] Display the movement count directly on the game window instead of the shell.
