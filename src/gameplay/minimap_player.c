#include "cub3d.h"

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
	t_minimap	*minimap;
	t_pointi	d;

	minimap = &game->minimap;
	d.y = -minimap->radius;
	while (d.y <= minimap->radius)
	{
		d.x = -minimap->radius;
		while (d.x <= minimap->radius)
		{
			if ((d.x * d.x) + (d.y * d.y) <= minimap->radius2)
			{
				put_pixel(minimap->pacman.x + d.x, minimap->pacman.y + d.y, \
														CLR_PLAYER, &game->img);
				if (is_in_fov((t_pointi){d.x, d.y}, &game->player))
					put_pixel(minimap->pacman.x + d.x, minimap->pacman.y + d.y,
						game->config.minimap_floor, &game->img);
			}
			d.x++;
		}
		d.y++;
	}
}
