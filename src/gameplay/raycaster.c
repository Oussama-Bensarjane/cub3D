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
		if (game->config.map[ray->map_y][ray->map_x] == '1')
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
static void	draw_line(t_game *game, t_ray *ray, int x, double wall_dist)
{
	t_textures			*texture;
	t_draw_line_info	l;
	double				step;
	double				tex_pos;

	texture = choose_texture(game, ray);
	calc_line_limits(wall_dist, &l.start, &l.end, &l.line_h);
	draw_ceiling(game, x, 0, l.start);
	l.tex_x = calc_tex_x(game, ray, texture->width, wall_dist);
	step = 1.0 * texture->height / l.line_h;
	tex_pos = calc_tex_step(texture, l.line_h, l.start);
	while (l.start < l.end)
	{
		l.tex_y = (int)tex_pos % texture->height;
		if (l.tex_y < 0)
			l.tex_y += texture->height;
		put_pixel(x, l.start++, get_pixel_clr(texture, l.tex_x, l.tex_y), game);
		tex_pos += step;
	}
	draw_floor(game, x, l.end, HEIGHT);
}

void	raycaster(t_player *player, t_game *game, double angle, int x)
{
	t_ray	ray;
	double	wall_dist;

	init_dda(player, &ray, angle);
	perform_dda(game, &ray);
	wall_dist = get_wall_dist(player, &ray, angle);
	draw_line(game, &ray, x, wall_dist);
}
