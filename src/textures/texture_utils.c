#include "cub3d.h"

int	convert_color(int color, int endian)
{
	int	r;
	int	g;
	int	b;

	if (!endian)
		return (color);
	else
	{
		r = (color >> 16) & 0xFF;
		g = (color >> 8) & 0xFF;
		b = color & 0xFF;
		return ((b << 16) | (g << 8) | r);
	}
}

int	calc_tex_x(int tex_width, double wall_dist, t_game *game)
{
	double	wall_x;
	int		tex_x;

	if (game->ray.side_hit == 0)
		wall_x = (game->player.p.y / BLOCK) + wall_dist * game->ray.dir.y;
	else
		wall_x = (game->player.p.x / BLOCK) + wall_dist * game->ray.dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex_width);
	if ((!game->ray.side_hit && game->ray.dir.x < 0)
		|| (game->ray.side_hit && game->ray.dir.y > 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}
