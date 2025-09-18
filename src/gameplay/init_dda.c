#include "cub3d.h"

static void	init_ray_dir(t_ray *ray, double angle)
{
	ray->dir_x = cos(angle);
	ray->dir_y = sin(angle);
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

static void	init_ray_step_x(t_player *player, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (player->x / BLOCK - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - player->x / BLOCK) * ray->delta_x;
	}
}

static void	init_ray_step_y(t_player *player, t_ray *ray)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (player->y / BLOCK - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - player->y / BLOCK) * ray->delta_y;
	}
}

void	init_dda(t_player *player, t_ray *ray, double angle)
{
	ray->map_x = player->x / BLOCK;
	ray->map_y = player->y / BLOCK;
	init_ray_dir(ray, angle);
	init_ray_step_x(player, ray);
	init_ray_step_y(player, ray);
}
