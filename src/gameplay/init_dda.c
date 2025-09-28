#include "cub3d.h"

static void	init_ray_dir(double angle, t_ray *ray)
{
	ray->dir.x = cos(angle);
	ray->dir.y = sin(angle);
	if (ray->dir.x == 0)
		ray->delta.x = 1e30;
	else
		ray->delta.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta.y = 1e30;
	else
		ray->delta.y = fabs(1 / ray->dir.y);
}

static void	init_ray_step_x(t_player *player, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side.x = (player->p.x / BLOCK - ray->map_x) * ray->delta.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side.x = (ray->map_x + 1.0 - player->p.x / BLOCK) * ray->delta.x;
	}
}

static void	init_ray_step_y(t_player *player, t_ray *ray)
{
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side.y = (player->p.y / BLOCK - ray->map_y) * ray->delta.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side.y = (ray->map_y + 1.0 - player->p.y / BLOCK) * ray->delta.y;
	}
}

void	init_dda(t_player *player, t_ray *ray)
{
	ray->map_x = player->p.x / BLOCK;
	ray->map_y = player->p.y / BLOCK;
	init_ray_dir(ray->angle, ray);
	init_ray_step_x(player, ray);
	init_ray_step_y(player, ray);
}
