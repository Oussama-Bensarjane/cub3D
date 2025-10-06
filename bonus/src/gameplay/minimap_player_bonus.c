#include "cub3d_bonus.h"

static int	is_in_fov(t_pointi d, t_player *player)
{
	static const double	half_fov = (FOV * (PI / 180)) / 2;
	double				len;
	double				dp;

	len = sqrt((d.x * d.x) + (d.y * d.y));
	if (len <= 0)
		return (0);
	dp = (player->cos_angle * d.x + player->sin_angle * d.y) / len;
	if (dp > 0 && dp >= cos(half_fov))
		return (1);
	return (0);
}

void	draw_minimap_player(t_game *game)
{
	static const int	center_px = \
MINIMAP_OFFSET_X + (MINIMAP_SCALE * MINIMAP_RADIUS) + (MINIMAP_SCALE / 2);
	static const int	center_py = \
MINIMAP_OFFSET_Y + (MINIMAP_SCALE * MINIMAP_RADIUS) + (MINIMAP_SCALE / 2);
	static const int	r = MINIMAP_SCALE / 2;
	static const int	r2 = r * r;
	t_pointi			d;

	d.y = -r;
	while (d.y <= r)
	{
		d.x = -r;
		while (d.x <= r)
		{
			if ((d.x * d.x) + (d.y * d.y) <= r2)
			{
				put_pixel(center_px + d.x, center_py + d.y, CLR_PLAYER, game);
				if (is_in_fov((t_pointi){d.x, d.y}, &game->player))
					put_pixel(center_px + d.x, center_py + d.y,
						game->config.minimap_floor, game);
			}
			d.x++;
		}
		d.y++;
	}
}
