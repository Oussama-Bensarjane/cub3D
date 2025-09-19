#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + (x * game->bpp) / 8;
	*(int *)(game->data + index) = color;
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

bool	touch(double px, double py, t_game *game)
{
	int		x;
	int		y;
	char	tile;

	x = px / BLOCK;
	y = py / BLOCK;
	tile = game->config.map[y][x];
	if (tile == '1')
		return (true);
	return (false);
}
