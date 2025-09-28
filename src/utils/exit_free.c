#include "cub3d.h"

void	exit_free(t_assets *cfg, char *msg)
{
	free_assets(cfg);
	ft_putendl_fd("Error", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	free_2d_array(char **arr)
{
	char	**ptr;

	if (!arr)
		return ;
	ptr = arr;
	while (*ptr)
		free(*ptr++);
	free(arr);
}

void	free_assets(t_assets *cfg)
{
	int	i;

	i = 0;
	while (i < TEX_MAX)
	{
		if (cfg->textures[i])
			free(cfg->textures[i]);
		cfg->textures[i] = NULL;
	}
	if (cfg->map)
		free_2d_array(cfg->map);
	cfg->map = NULL;
}
