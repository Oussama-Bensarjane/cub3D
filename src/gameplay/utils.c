#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_img *img)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * img->size_line + (x * img->bpp) / 8;
	*(int *)(img->data + index) = color;
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;
	double		dx;

	(void)y;
	if (game->player.key[KEY_V] || game->player.key[KEY_H])
		return (0);
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

void	draw_help_screen(t_game *game)
{
	t_texture	*help;

	help = &game->config.textures[TEX_HELP];
	mlx_put_image_to_window(game->mlx, game->win, help->img.img,
		help->width, 0);
}

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
