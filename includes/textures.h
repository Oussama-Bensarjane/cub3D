#ifndef TEXTURES_H
# define TEXTURES_H
# define TEXTR_F "Failed to load texture file"
# define TEXTR_DT "Failed to get texture data"

/**
 * @brief Loads all wall and sprite textures into memory.
 *
 * Reads texture files from the provided paths and stores them
 * in the game's texture array for rendering.
 *
 * @param game   Pointer to the main game structure.
 * @param paths  Array of texture file paths (size TEX_MAX).
 */
void	load_textures(t_game *game, char *paths[TEX_MAX]);

/**
 * @brief Converts a color value based on the system's endianness.
 *
 * Ensures that RGB color components are stored correctly for display.
 *
 * @param color   Color value in 0xRRGGBB format.
 * @param endian  Byte order flag (0 for little-endian, 1 for big-endian).
 * @return Converted color value suitable for rendering.
 */
int		convert_color(int color, int endian);

/**
 * @brief Calculates the X coordinate of the texture to sample from.
 *
 * Determines which vertical slice of the wall texture to use
 * based on hit position and player viewing direction.
 *
 * @param text_width  Width of the texture in pixels.
 * @param wall_dist   Distance to the wall along the ray.
 * @param game        Pointer to the main game structure.
 * @return Texture X coordinate (0–text_width-1).
 */
int		calc_tex_x(int text_width, double wall_dist, t_game *game);

/**
 * @brief Draws the ceiling portion of a column.
 *
 * Fills pixels above the wall slice with the ceiling color.
 *
 * @param x       X coordinate of the column on screen.
 * @param end_y   Y coordinate where the wall begins.
 * @param color   Ceiling color in 0xRRGGBB format.
 * @param img     Pointer to the image buffer.
 */
void	draw_ceiling(int x, int end_y, int color, t_img *img);

/**
 * @brief Draws a vertical wall slice at a given screen column.
 *
 * Samples from the correct wall texture based on raycast results
 * and writes the pixels into the image buffer.
 *
 * @param x     X coordinate of the column on screen.
 * @param game  Pointer to the main game structure.
 */
void	draw_wall(int x, t_game *game);

/**
 * @brief Draws the floor portion of a column.
 *
 * Fills pixels below the wall slice with the floor color.
 *
 * @param x        X coordinate of the column on screen.
 * @param start_y  Y coordinate where the wall ends.
 * @param color    Floor color in 0xRRGGBB format.
 * @param img      Pointer to the image buffer.
 */
void	draw_floor(int x, int start_y, int color, t_img *img);

/**
 * @brief Frees all dynamically allocated texture path strings.
 *
 * Used to clean up texture path arrays after initialization.
 *
 * @param paths  Array of texture path strings (size TEX_MAX).
 */
void	free_textures_paths(char *paths[TEX_MAX]);

#endif
