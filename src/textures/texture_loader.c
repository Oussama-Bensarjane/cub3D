#include "cub3d.h"

void	load_textures(t_game *game, char *paths[TEX_MAX])
{
	int			i;
	t_texture	*textures;

	textures = game->config.textures;
	paths[TEX_DOOR] = ft_strdup(TEX_DOOR_PATH);
	paths[TEX_HELP] = ft_strdup(TEX_HELP_PATH);
	i = -1;
	while (++i < TEX_MAX)
	{
		textures[i].img.img = mlx_xpm_file_to_image(game->mlx, paths[i], \
&textures[i].width, &textures[i].height);
		if (!textures[i].img.img)
		{
			printf(RED"Error\n"END"path: "YELLOW"%s\n", paths[i]);
			free_textures_paths(paths);
			game_over(game, END TEXTR_F, EXIT_FAILURE);
		}
		textures[i].img.data = mlx_get_data_addr(textures[i].img.img, \
&textures[i].img.bpp, &textures[i].img.size_line, &textures[i].img.endian);
		if (!textures[i].img.data)
			(printf(RED"Error\n"END"path: "YELLOW"%s\n", paths[i]), \
free_textures_paths(paths), game_over(game, END TEXTR_DT, EXIT_FAILURE));
	}
	free_textures_paths(paths);
	textures[TEX_HELP].width = WIDTH - textures[TEX_HELP].width;
}
