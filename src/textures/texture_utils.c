#include "cub3d.h"

/*
** Choose texture of the wall hit by the ray
*/
t_textures	*choose_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0) // hit a vertical wall (X-axis step)
	{
		if (ray->dir_x > 0)
			return (&game->config.ea);
		else
			return (&game->config.we);
	}
	else // hit a horizontal wall (Y-axis step)
	{
		if (ray->dir_y > 0)
			return (&game->config.so);
		else
			return (&game->config.no);
	}
}

/*
** Return the color of the pixel at (x, y) in the texture
*/
int	get_pixel_clr(t_textures *tex, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color & 0x00FFFFFF); // ignore alpha if present
}

// Calculate line height and start/end positions
void	calc_line_limits(double wall_dist, int *start, int *end, int *line_h)
{
	double	dist_proj_plane;

	dist_proj_plane = WIDTH / (2 * tan((FOV * PI) / 360.0));
	*line_h = dist_proj_plane / wall_dist;
	*start = (HEIGHT - *line_h) / 2;
	if (*start < 0)
		*start = 0;
	*end = *start + *line_h;
	if (*end >= HEIGHT)
		*end = HEIGHT - 1;
}

// Compute exact wall hit position and texture X
int	calc_tex_x(t_game *game, t_ray *ray, int tex_width, double wall_dist)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = (game->player.y / BLOCK) + wall_dist * ray->dir_y;
	else
		wall_x = (game->player.x / BLOCK) + wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex_width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

// Calculate texture stepping
double	calc_tex_step(t_textures *texture, int line_h, int start)
{
	double	step;
	double	tex_pos;

	step = 1.0 * texture->height / line_h;
	tex_pos = (start - HEIGHT / 2 + line_h / 2) * step;
	if (start < 0)
		tex_pos -= start * step;
	return (tex_pos);
}
