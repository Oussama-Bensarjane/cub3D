#include "cub3d.h"

static int	choose_texture(t_game *game)
{
	if (game->config.map[game->ray.map_y][game->ray.map_x] == 'D')
		return (TEX_DOOR);
	else if (game->ray.side_hit == 0)
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

static int	get_pixel_clr(int x, int y, t_texture *tex)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->img.data + (y * tex->img.size_line + x * (tex->img.bpp / 8));
	return (*(unsigned int *)pixel);
}

void	draw_ceiling(int x, int end_y, int color, t_img *img)
{
	int	y;

	y = 0;
	while (y < end_y)
		put_pixel(x, y++, color, img);
}

void	draw_floor(int x, int start_y, int color, t_img *img)
{
	while (start_y < HEIGHT)
		put_pixel(x, start_y++, color, img);
}

void	draw_wall(int x, t_game *game)
{
	t_texture	*texture;
	t_wall		*wall;
	t_pointi	tex;
	double		tex_y_pos;
	double		step;

	texture = &game->config.textures[choose_texture(game)];
	wall = &game->ray.wall;
	step = (1.0 * texture->height) / wall->height;
	tex.x = calc_tex_x(texture->width, wall->dist, game);
	tex_y_pos = (wall->start - HEIGHT / 2 + wall->height / 2) * step;
	while (wall->start < wall->end)
	{
		tex.y = (int)tex_y_pos % texture->height;
		if (tex.y < 0)
			tex.y += texture->height;
		put_pixel(x, wall->start++,
			convert_color(get_pixel_clr(tex.x, tex.y, texture),
				game->img.endian), &game->img);
		tex_y_pos += step;
	}
}
