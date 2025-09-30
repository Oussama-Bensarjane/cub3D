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

bool	touch(t_point p, t_game *game)
{
	int		x;
	int		y;
	char	tile;

	x = p.x / BLOCK;
	y = p.y / BLOCK;
	tile = game->config.map[y][x];
	if (tile == '1')
		return (true);
	return (false);
}
