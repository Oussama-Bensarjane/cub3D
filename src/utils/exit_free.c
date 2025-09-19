#include "cub3d.h"

void	exit_free(t_assets *cfg, char *msg)
{
	free_config(cfg);
	ft_putendl_fd("Error", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	exit (1);
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

void	free_config(t_assets *cfg)
{
	if (cfg->tex_no)
		free(cfg->tex_no);
	if (cfg->tex_so)
		free(cfg->tex_so);
	if (cfg->tex_we)
		free(cfg->tex_we);
	if (cfg->tex_ea)
		free(cfg->tex_ea);
	if (cfg->map)
		free_2d_array(cfg->map);
	cfg->tex_no = NULL;
	cfg->tex_so = NULL;
	cfg->tex_we = NULL;
	cfg->tex_ea = NULL;
	cfg->map = NULL;
}

