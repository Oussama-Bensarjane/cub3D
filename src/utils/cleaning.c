#include "cub3d.h"

void	free_config(t_config *cfg)
{
	int	i;

	if (cfg->tex_no)
		free(cfg->tex_no);
	if (cfg->tex_so)
		free(cfg->tex_so);
	if (cfg->tex_we)
		free(cfg->tex_we);
	if (cfg->tex_ea)
		free(cfg->tex_ea);

	if (cfg->map)
	{
		i = 0;
		while (i < cfg->map_height)
			free(cfg->map[i++]);
		free(cfg->map);
	}

	cfg->tex_no = NULL;
	cfg->tex_so = NULL;
	cfg->tex_we = NULL;
	cfg->tex_ea = NULL;
	cfg->map = NULL;
}

void	cleanup(t_config *cfg)
{
	free_config(cfg);

	/*
	 * Engine part cleaning ...
	 */

}