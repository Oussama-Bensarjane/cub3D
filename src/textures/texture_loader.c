#include "cub3d.h"

static void	init_texture(t_textures *tex)
{
	tex->ptr = NULL;
	tex->addr = NULL;
	tex->width = 0;
	tex->height = 0;
	tex->bpp = 0;
	tex->line_len = 0;
	tex->endian = 0;
}

static void	load_texture(t_game *game, t_textures *tex, char *path)
{
	tex->ptr = mlx_xpm_file_to_image(game->mlx, path, &tex->width, \
&tex->height);
	if (!tex->ptr)
		game_over(game, "Error: Failed to load texture file", EXIT_FAILURE);
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->line_len, \
&tex->endian);
	if (!tex->addr)
		game_over(game, "Error: Failed to get texture data", EXIT_FAILURE);
}

void	init_load_textures(t_game *game, t_assets *config)
{
	init_texture(&game->config.no);
	init_texture(&game->config.so);
	init_texture(&game->config.we);
	init_texture(&game->config.ea);
	load_texture(game, &game->config.no, config->tex_no);
	load_texture(game, &game->config.so, config->tex_so);
	load_texture(game, &game->config.we, config->tex_we);
	load_texture(game, &game->config.ea, config->tex_ea);
}

void	draw_ceiling(t_game *game, int x, int start_y, int end_y)
{
	int	y;

	y = start_y;
	while (y < end_y)
		put_pixel(x, y++, game->config.ceiling, game);
}

void	draw_floor(t_game *game, int x, int start_y, int end_y)
{
	int	y;

	y = start_y;
	while (y < end_y)
		put_pixel(x, y++, game->config.floor, game);
}
