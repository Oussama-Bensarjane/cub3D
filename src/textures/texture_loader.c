#include "cub3d.h"

static void	init_textures(t_texture *textures)
{
	int	i;

	i = 0;
	while (i < TEX_MAX)
	{
		textures[i].img = (t_img){NULL, NULL, 0, 0, 0};
		textures[i].width = 0;
		textures[i].height = 0;
		i++;
	}
}

static void	load_textures(t_game *game, char *paths[TEX_MAX])
{
	int			i;
	t_texture	*textures;

	textures = game->config.textures;
	i = 0;
	while (i < TEX_MAX)
	{
		textures[i].img.img = mlx_xpm_file_to_image(game->mlx, paths[i], \
&textures[i].width, &textures[i].height);
		free(paths[i]);
		paths[i] = NULL;
		if (!textures[i].img.img)
			game_over(game, "Error: Failed to load texture file", EXIT_FAILURE);
		textures[i].img.data = mlx_get_data_addr(textures[i].img.img, \
&textures[i].img.bpp, &textures[i].img.size_line, &textures[i].img.endian);
		if (!textures[i].img.data)
			game_over(game, "Error: Failed to get texture data", EXIT_FAILURE);
		i++;
	}
}

void	init_load_textures(t_game *game, char *textures_paths[TEX_MAX])
{
	init_textures(game->config.textures);
	load_textures(game, textures_paths);
}
