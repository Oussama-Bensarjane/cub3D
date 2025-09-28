#include "cub3d.h"

/*
** Choose texture of the wall hit by the ray
* side = 0 -> hit a vertical wall (X-axis step)
* side = 1 -> hit a horizontal wall (Y-axis step)
*/
static int	choose_texture(t_game *game)
{
	if (game->ray.side_hit == 0)
	{
		if (game->ray.dir.x > 0)
			return (TEX_EA);
		else
			return (TEX_WE);
	}
	else
	{
		if (game->ray.dir.y > 0)
			return (TEX_SO);
		else
			return (TEX_NO);
	}
}

/*
** Return the color of the pixel at (x, y) in the texture
* (color & 0x00FFFFFF) -->  Ignore alpha if present
*/
static int	get_pixel_clr(int x, int y, t_texture *tex)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->img.data + (y * tex->img.size_line + x * (tex->img.bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_ceiling(int x, int start_y, int end_y, t_game *game)
{
	while (start_y < end_y)
		put_pixel(x, start_y++, game->config.ceiling, game);
}

void	draw_floor(int x, int start_y, int end_y, t_game *game)
{
	while (start_y < end_y)
		put_pixel(x, start_y++, game->config.floor, game);
}

void	draw_wall(int x, t_game *game)
{
	t_texture	*texture;
	t_wall		*wall;
	int			tex_x;
	int			tex_y;
	double		tex_pos;

	texture = &game->config.textures[choose_texture(game)];
	wall = &game->ray.wall;
	tex_x = calc_tex_x(texture->width, wall->dist, game);
	tex_pos = calc_tex_step(texture->height, wall->height, wall->start);
	while (wall->start < wall->end)
	{
		tex_y = (int)tex_pos % texture->height;
		if (tex_y < 0)
			tex_y += texture->height;
		put_pixel(x, wall->start++, convert_color(\
			get_pixel_clr(tex_x, tex_y, texture), game->img.endian), game);
		tex_pos += (1.0 * texture->height) / wall->height;
	}
}
