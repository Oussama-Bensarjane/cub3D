#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include "config_bonus.h"
# include "parser_bonus.h"
# include "textures_bonus.h"
# include "sprites_bonus.h"

/**
 * game_over
 * clean up all the resources
 * In case of error prints an error message to stderr
 * exits the program.
 *
 * @param game pointer to the game resources
 * @param msg  The error message to display OR (NULL)
 * @param exit_status exit with 1 in case of error or 0 for success
 */
void	game_over(t_game *game, char *msg, int exit_status);

/**
 * init_game
 * Initializes the game structure:
 *   - Loads the map
 *   - Initializes the player
 *   - Sets up the MLX window and image buffer
 *
 * @param game  Pointer to the game structure to initialize
 */
void	init_game(t_game *game, t_assets *assets);

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

/**
 * can_move
 * Checks if the player can move to P(new_x, new_y) without colliding with walls.
 * Adds a "radius" to avoid clipping through corners.
 */
bool	can_move(t_point p, t_game *game);

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
void	clear_image(t_game *game);

/**
 * touch
 * Checks if the given position (p.x, p.y) is inside a wall block.
 *
 * @param p    (X, Y) position in the world (double, not grid index).
 * @param game  Pointer to game data (contains the map).
 *
 * @return true  If the position is within a wall block ('1').
 * @return false Otherwise (free space).
 */
bool	touch(t_point p, t_game *game);

void	init_dda(t_player *player, t_ray *ray);

void	raycaster(int x, t_game *game);

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

void	draw_minimap(t_game *game);
void	draw_circle_outline(t_game *game, int color);
void	draw_minimap_player(t_game *game);
void	try_toggle_door(t_game *game);

#endif
