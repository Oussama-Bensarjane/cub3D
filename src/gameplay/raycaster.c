#include "cub3d.h"

static void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static double	get_wall_dist(t_player *player, t_ray *ray, double angle)
{
	double	dist;

	if (ray->side == 0)
		dist = (ray->map_x - player->x / BLOCK
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		dist = (ray->map_y - player->y / BLOCK
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	return (dist * cos(angle - player->angle));
}

static void	draw_line(t_game *game, int x, double wall_dist)
{
	double	dist_proj_plane;
	int		line_h;
	int		start;
	int		end;

	dist_proj_plane = WIDTH / (2 * tan((FOV * PI) / 360.0));
	line_h = dist_proj_plane / wall_dist;
	start = (HEIGHT - line_h) / 2;
	if (start < 0)
		start = 0;
	end = start + line_h;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (start < end)
	{
		put_pixel(x, start, 0x00FF00, game);
		start++;
	}
}

void	raycaster(t_player *player, t_game *game, double angle, int x)
{
	t_ray	ray;
	double	wall_dist;

	init_dda(player, &ray, angle);
	perform_dda(game, &ray);
	wall_dist = get_wall_dist(player, &ray, angle);
	draw_line(game, x, wall_dist);
}
