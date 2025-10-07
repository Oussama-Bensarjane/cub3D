#include "cub3d_bonus.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->img.size_line + (x * game->img.bpp) / 8;
	*(int *)(game->img.data + index) = color;
}

void	clear_image(t_game *game)
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

int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;
	double		dx;

	(void)y;
	if (last_x == -1)
		last_x = x;
	dx = x - last_x;
	if (dx != 0)
	{
		game->player.angle += dx * MOUSE_SENSITIVITY;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		else if (game->player.angle >= 2 * PI)
			game->player.angle -= 2 * PI;
	}
	last_x = x;
	return (0);
}

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
static bool	touch(t_point p, t_game *game)
{
	int		x;
	int		y;
	char	tile;

	x = p.x / BLOCK;
	y = p.y / BLOCK;
	tile = game->config.map[y][x];
	if (tile == '1' || tile == 'D')
		return (true);
	return (false);
}

bool	can_move(t_point p, t_game *game)
{
	if (touch(p, game))
		return (false);
	else if (touch((t_point){p.x - PLAYER_RADIUS, p.y}, game))
		return (false);
	else if (touch((t_point){p.x + PLAYER_RADIUS, p.y}, game))
		return (false);
	else if (touch((t_point){p.x, p.y - PLAYER_RADIUS}, game))
		return (false);
	else if (touch((t_point){p.x, p.y + PLAYER_RADIUS}, game))
		return (false);
	return (true);
}
