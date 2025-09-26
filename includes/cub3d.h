#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include "config.h"
# include "parser.h"
# include "textures.h"

/**
 * exit_failure
 * Prints an error message to standard error and exits the program.
 *
 * @param msg  The error message to display
 */
void	exit_failure(char *msg);
void	game_over(t_game *game, char *msg, int exit_status);
void	free_textures(t_game *game);

/**
 * init_player
 * Initializes the player at cpecific position of the screen with default values.
 */
void	init_player(t_player *player, t_assets *config);

/**
 * key_press
 * Handles key press events, updating player state accordingly.
 * Special case: ESC exits the game.
 */
int		key_press(int keycode, t_game *game);

/**
 * key_release
 * Handles key release events, resetting movement/rotation flags.
 */
int		key_release(int keycode, t_player *player);

/**
 * move_player
 * Updates player position and angle based on pressed keys.
 * Handles:
 *   - Forward/backward movement (W, S)
 *   - Strafing (A, D)
 *   - Rotation (LEFT, RIGHT)
 * Also ensures player cannot walk through walls.
 */
void	move_player(t_game *game);
void	update_position(t_player *player, t_game *game,\
	double new_x, double new_y);

/**
 * put_pixel
 * Draws a single pixel of a given color at (x, y) on the game's buffer.
 *
 * @param x       The horizontal coordinate of the pixel.
 * @param y       The vertical coordinate of the pixel.
 * @param color   The color value in 0xRRGGBB format (Little endian).
 * @param game    Pointer to the game structure containing image data.
 */
void	put_pixel(int x, int y, int color, t_game *game);

/**
 * clear_image
 * Fills the entire image with black pixels.
 *
 * @note This works by looping through every (x, y) coordinate
 *       and writing a black pixel (color = 0).
 */
void	clear_image(t_game *game);

/**
 * touch
 * Checks if the given position (px, py) is inside a wall block.
 *
 * @param px    X position in the world (double, not grid index).
 * @param py    Y position in the world (double, not grid index).
 * @param game  Pointer to game data (contains the map).
 *
 * @return true  If the position is within a wall block ('1').
 * @return false Otherwise (free space).
 */
bool	touch(double px, double py, t_game *game);

void	init_dda(t_player *player, t_ray *ray, double angle);

void	raycaster(t_player *player, t_game *game, double angle, int x);

/**
 * draw_loop
 * Main rendering loop called every frame.
 *
 * Steps:
 *   1. Update player position based on pressed keys.
 *   2. Clear the screen buffer.
 *   3. Cast rays for each vertical column on screen and draw wall slices.
 *   4. Push the final image to the window.
 *
 * @param game  Pointer to the game structure (player, map, image, etc.)
 * @return 0   Standard return for MLX loop hook
 */
int		draw_loop(t_game *game);
#endif
