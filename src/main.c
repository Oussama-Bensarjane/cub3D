#include "cub3d.h"

static void	init_config(t_config *cfg)
{
	cfg->tex_no = NULL;
	cfg->tex_so = NULL;
	cfg->tex_we = NULL;
	cfg->tex_ea = NULL;
	cfg->floor_color = -1;
	cfg->ceiling_color = -1;
	cfg->map = NULL;
	cfg->map_width = 0;
	cfg->map_height = 0;
	cfg->player_x = -1;
	cfg->player_y = -1;
	cfg->player_dir = '\0';
}

int main(int ac, char **av)
{
	t_config cfg;

	if (ac != 2)
	{
		printf("Error: usage: %s <map.cub>\n", av[0]);
		return (1);
	}
	init_config(&cfg);

	if (parse_file(&cfg, av[1]) == -1)
	{
		free_config(&cfg);
		return (1);
	}
	/*	testing... */
	for (int i = 0; cfg.map[i]; i++)
    	printf("[%s]\n", cfg.map[i]);
	printf("cfg.map_height %d\n", cfg.map_height);
	printf("cfg.map_width %d\n", cfg.map_width);
	/* ---------  */


	cleanup(&cfg);

	return (0);
}