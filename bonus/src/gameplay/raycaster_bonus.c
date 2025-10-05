#include "cub3d_bonus.h"

static void	perform_dda(char **map, t_ray *ray)
{
	char	tile;
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->map_x += ray->step_x;
			ray->side_hit = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->map_y += ray->step_y;
			ray->side_hit = 1;
		}
		tile = map[ray->map_y][ray->map_x];
		if (tile == '1' || tile == 'D')
			hit = true;
	}
}

static void	set_wall_dist(t_player *player, t_ray *ray)
{
	if (ray->side_hit == 0)
		ray->wall.dist = (ray->map_x - player->p.x / BLOCK \
						+ (1 - ray->step_x) / 2) / ray->dir.x;
	else
		ray->wall.dist = (ray->map_y - player->p.y / BLOCK \
						+ (1 - ray->step_y) / 2) / ray->dir.y;
}

/*
 * 			Draw_line:
 *
 * Draws a vertical column on screen at x:
 * 	 ceiling, textured wall slice, and floor, using the ray
 * 		 hit info and wall distance for correct perspective.
 * calc_line_limits --> Computes the top and bottom y-coordinates
 * 					of the wall slice for a given wall distance.
 * calc_tex_x       --> Calculates the horizontal texture coordinate
 * 					for the wall slice based on ray hit.
 * calc_tex_step    --> Computes the vertical step in the texture
 * 					per screen pixel for wall rendering.
 */
static void	draw_line(int x, t_game *game)
{
	t_wall	*wall;
	double	dist_proj_plane;

	wall = &game->ray.wall;
	dist_proj_plane = WIDTH / (2 * tan((FOV * PI) / 360.0));
	wall->height = dist_proj_plane / \
		(wall->dist * cos(game->ray.angle - game->player.angle));
	wall->start = (HEIGHT - wall->height) / 2;
	if (wall->start < 0)
		wall->start = 0;
	wall->end = wall->start + wall->height;
	if (wall->end >= HEIGHT)
		wall->end = HEIGHT - 1;
	draw_ceiling(x, 0, wall->start, game);
	draw_wall(x, game);
	draw_floor(x, wall->end, HEIGHT, game);
}

void	raycaster(int x, t_game *game)
{
	init_dda(&game->player, &game->ray);
	perform_dda(game->config.map, &game->ray);
	set_wall_dist(&game->player, &game->ray);
	draw_line(x, game);
}
