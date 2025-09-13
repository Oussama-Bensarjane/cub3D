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

static void	test(t_config *cfg)
{
	for (int i = 0; cfg->map[i]; i++)
    	printf("[%s]\n", cfg->map[i]);
	printf("--------------------\n");
	printf("cfg->map_height %d\n", cfg->map_height);
	printf("cfg->map_width %d\n", cfg->map_width);
	printf("--------------------\n");
	printf("NO --> %s\n", cfg->tex_no);
	printf("WE --> %s\n", cfg->tex_we);
	printf("EA --> %s\n", cfg->tex_ea);
	printf("SO --> %s\n", cfg->tex_so);
	printf("--------------------\n");
	printf("F --> %X\n", cfg->floor_color);
	printf("C --> %X\n", cfg->ceiling_color);
	printf("--------------------\n");
	printf("player_dir :[%c]\n", cfg->player_dir);
	printf("player_x :[%d]\n", cfg->player_x);
	printf("player_y :[%d]\n", cfg->player_y);

}
void	f()
{
	system("leaks cub3D");
}

int main(int ac, char **av)
{
	// atexit(f);
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
		return (10);
	}
	/*	testing... */
	test(&cfg);
	/* ---------  */

	cleanup(&cfg);
	return (0);
}