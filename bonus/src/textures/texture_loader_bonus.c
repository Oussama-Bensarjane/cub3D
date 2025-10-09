#include "cub3d_bonus.h"

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
	paths[TEX_DOOR] = ft_strdup(TEX_DOOR_PATH);
	i = 0;
	while (i < TEX_MAX)
	{
		textures[i].img.img = mlx_xpm_file_to_image(game->mlx, paths[i], \
&textures[i].width, &textures[i].height);
		if (!textures[i].img.img)
		{
			free_textures_paths(paths);
			game_over(game, "Error: Failed to load texture file", EXIT_FAILURE);
		}
		textures[i].img.data = mlx_get_data_addr(textures[i].img.img, \
&textures[i].img.bpp, &textures[i].img.size_line, &textures[i].img.endian);
		if (!textures[i].img.data)
		{
			free_textures_paths(paths);
			game_over(game, "Error: Failed to get texture data", EXIT_FAILURE);
		}
		i++;
	}
	free_textures_paths(paths);
}

void	init_load_texture_and_sprites(t_game *game, char *paths[TEX_MAX])
{
	t_weapon	*w;
	int			j;

	init_textures(game->config.textures);
	j = 0;
	while (j < W_MAX)
	{
		w = &game->sprite.weapons[j];
		init_weapon(w, j);
		j++;
	}
	load_textures(game, paths);
	load_weapons(game);
}
