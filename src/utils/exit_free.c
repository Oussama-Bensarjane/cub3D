#include "cub3d.h"

void	exit_free(t_assets *cfg, char *line, char *msg, char *path)
{
	char	*tmp;

	if (msg)
	{
		ft_putendl_fd(RED"Error"END, 2);
		ft_putendl_fd(msg, 2);
	}
	if (path)
		printf("path: "YELLOW"%s\n"END, path);
	if (line)
		(printf(YELLOW"%s"END, line), free(line));
	free_assets(cfg);
	if (cfg->fd != -1)
	{
		tmp = get_next_line(cfg->fd);
		while (tmp)
		{
			free(tmp);
			tmp = get_next_line(cfg->fd);
		}
		close(cfg->fd);
		cfg->fd = -1;
	}
	exit (EXIT_FAILURE);
}

void	exit_enclosure(t_assets *cfg, int x, int y)
{
	ft_putendl_fd(RED"Error"END, 2);
	ft_putendl_fd("Map not enclosed", 2);
	if (y == 0)
		printf(YELLOW"Check 1st horizantal line\n%s\n"END, cfg->map[y]);
	else if (y == cfg->map_height - 1)
		printf(YELLOW"Check last horizantal line\n%s\n"END, cfg->map[y]);
	else if (x == 0)
		printf(YELLOW"Check 1st vertical line\n%s\n"END, cfg->map[y]);
	else if (x == cfg->map_width - 1)
		printf(YELLOW"Check last vertical line\n%s\n"END, cfg->map[y]);
	(free_assets(cfg), exit (EXIT_FAILURE));
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

void	free_textures_paths(char *paths[TEX_MAX])
{
	int	i;

	i = 0;
	while (i < TEX_MAX)
	{
		if (paths[i])
			free(paths[i]);
		paths[i] = NULL;
		i++;
	}
}

void	free_assets(t_assets *cfg)
{
	free_textures_paths(cfg->textures);
	if (cfg->map)
		free_2d_array(cfg->map);
	cfg->map = NULL;
}
