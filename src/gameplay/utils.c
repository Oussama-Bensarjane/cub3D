# include "cub3d.h"

/**
 * put_pixel
 * Draws a single pixel of a given color at (x, y) on the game's buffer.
 *
 * @param x       The horizontal coordinate of the pixel.
 * @param y       The vertical coordinate of the pixel.
 * @param color   The color value in 0xRRGGBB format.
 * @param game    Pointer to the game structure containing image data.
 */
void put_pixel(int x, int y, int color, t_game *game)
{
	int index;

	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + (x * game->bpp) / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

/**
 * clear_image
 * Fills the entire image with black pixels.
 *
 * @note This works by looping through every (x, y) coordinate
 *       and writing a black pixel (color = 0).
 */
void clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

/**
 * fixed_distance
 * Computes the distance between two points (x1, y1) and (x2, y2),
 * then adjusts it based on the player's viewing angle to remove
 * the fish-eye effect in ray-casting (cosine correction).
 *
 * @param x1    Starting x position
 * @param y1    Starting y position
 * @param x2    Target x position
 * @param y2    Target y position
 * @param game  Pointer to game data (for player angle)
 *
 * @return Corrected distance between the two points
 */
double	fixed_distance(double x1, double y1, double x2, double y2, t_game *game)
{
	double	delta_x;
	double	delta_y;
	double	angle;
	double	dist;

	// Differences between the two points
	delta_x = x2 - x1;
	delta_y = y2 - y1;

	// Angle between the ray and player's direction
	angle = atan2(delta_y, delta_x) - game->player.angle;

	// Euclidean distance corrected with cos(angle) to fix fish-eye
	dist = sqrt((delta_x * delta_x) + (delta_y * delta_y)) * cos(angle);
	return (dist);
}

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
bool	touch(double px, double py, t_game *game)
{
	int		x;
	int		y;
	char	tile;

	x = px / BLOCK;
	y = py / BLOCK;
	if (y > 9)
		return (true);
	if ((size_t)x >= ft_strlen(game->map[y]))
		return (true);
	tile = game->map[y][x];
	if(tile == '1' || tile == ' ')
		return (true);
	return (false);
}
