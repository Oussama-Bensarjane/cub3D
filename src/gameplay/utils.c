#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + (x * game->bpp) / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
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

double	fixed_distance(double x1, double y1, double x2, double y2, t_game *game)
{
	double	delta_x;
	double	delta_y;
	double	angle;
	double	dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	dist = sqrt((delta_x * delta_x) + (delta_y * delta_y)) * cos(angle);
	return (dist);
}

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
	if (tile == '1')
		return (true);
	return (false);
}
