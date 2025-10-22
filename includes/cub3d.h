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
# include "sprites.h"

/**
 * @brief Frees all allocated resources and terminates the program.
 *
 * Prints an optional error message to stderr before exiting.
 *
 * @param game         Pointer to the main game structure.
 * @param msg          Optional error message (NULL for none).
 * @param exit_status  Exit code (1 for error, 0 for normal exit).
 */
void	game_over(t_game *game, char *msg, int exit_status);

/**
 * @brief Initializes the core game systems.
 *
 * Sets up the map, player, and MLX window/image buffer.
 *
 * @param game    Pointer to the main game structure.
 * @param assets  Pointer to preloaded map and texture data.
 */
void	init_game(t_game *game, t_assets *assets);

/**
 * @brief Loads all wall textures and sprite images into memory.
 *
 * @param game   Pointer to the main game structure.
 * @param paths  Array of file paths to texture images (size TEX_MAX).
 */
void	init_load_textures_and_sprites(t_game *game, char *paths[TEX_MAX]);

/**
 * @brief Initializes the player with default values and starting position.
 *
 * @param player  Pointer to the player structure.
 * @param config  Pointer to the parsed configuration/map data.
 */
void	init_player(t_player *player, t_assets *config);

/**
 * @brief Handles keyboard key press events.
 *
 * Updates movement or rotation states.  
 * Pressing ESC triggers game exit.
 *
 * @param keycode  Key identifier.
 * @param game     Pointer to the main game structure.
 * @return Always returns 0 (MLX event convention).
 */
int		key_press(int keycode, t_game *game);

/**
 * @brief Handles keyboard key release events.
 *
 * Resets movement and rotation flags when keys are released.
 *
 * @param keycode  Key identifier.
 * @param player   Pointer to the player structure.
 * @return Always returns 0 (MLX event convention).
 */
int		key_release(int keycode, t_player *player);

/**
 * @brief Handles mouse movement for camera rotation.
 *
 * @param x     Current mouse X position.
 * @param y     Current mouse Y position.
 * @param game  Pointer to the main game structure.
 * @return Always returns 0 (MLX event convention).
 */
int		mouse_move(int x, int y, t_game *game);

/**
 * @brief Moves the player according to current input state.
 *
 * Supports forward/backward (W/S), strafing (A/D), and rotation (←/→).  
 * Prevents collision with walls.
 *
 * @param game  Pointer to the main game structure.
 */
void	move_player(t_game *game);

/**
 * @brief Checks if a position is walkable (not inside a wall).
 *
 * Adds a collision radius to avoid clipping through corners.
 *
 * @param p     Target position to test.
 * @param game  Pointer to the main game structure.
 * @return true if movement is allowed, false otherwise.
 */
bool	can_move(t_point p, t_game *game);

/**
 * @brief Draws a single pixel on the given image buffer.
 *
 * @param x      X coordinate.
 * @param y      Y coordinate.
 * @param color  Color value in 0xRRGGBB format.
 * @param img    Pointer to the target image buffer.
 */
void	put_pixel(int x, int y, int color, t_img *img);

/**
 * @brief Initializes DDA (Digital Differential Analyzer) for raycasting.
 *
 * @param player  Pointer to the player structure.
 * @param ray     Pointer to the ray structure to initialize.
 */
void	init_dda(t_player *player, t_ray *ray);

/**
 * @brief Performs raycasting for a single vertical stripe.
 *
 * Computes wall distances, textures, and draws the column.
 *
 * @param x     Screen column index.
 * @param game  Pointer to the main game structure.
 */
void	raycaster(int x, t_game *game);

/**
 * @brief Main render loop, executed once per frame.
 *
 * Steps:
 *   1. Update player movement.
 *   2. Clear the frame buffer.
 *   3. Cast rays for each column.
 *   4. Render the image to the window.
 *
 * @param game  Pointer to the main game structure.
 * @return Always returns 0 (MLX loop hook convention).
 */
int		draw_loop(t_game *game);

/**
 * @brief Draws the minimap overlay.
 *
 * Includes map tiles, player, and environment layout.
 *
 * @param game  Pointer to the main game structure.
 */
void	draw_minimap(t_game *game);

/**
 * @brief Draws a circular border around the minimap.
 *
 * @param game   Pointer to the main game structure.
 * @param color  Circle outline color.
 */
void	draw_circle_outline(t_game *game, int color);

/**
 * @brief Draws the player icon on the minimap.
 *
 * @param game  Pointer to the main game structure.
 */
void	draw_minimap_player(t_game *game);

/**
 * @brief Attempts to open or close a nearby door.
 *
 * Checks proximity and toggles door state if possible.
 *
 * @param game  Pointer to the main game structure.
 */
void	try_toggle_door(t_game *game);

/**
 * @brief Displays a help or control instruction screen.
 *
 * @param game  Pointer to the main game structure.
 */
void	draw_help_screen(t_game *game);

#endif
