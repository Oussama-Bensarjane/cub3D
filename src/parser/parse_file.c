#include "cub3d.h"

static void	parse_config_section(t_assets *cfg, int *stage, char *line)
{
	if (is_map_line(line))
	{
		validate_config(cfg, line);
		*stage = 1;
		add_map_line(cfg, line);
	}
	else if (line[0] != '\n')
		parse_config_line(cfg, line);
}

static void	parse_map_section(t_assets *cfg, char *line)
{
	int	i;
	int	only_space;

	only_space = 1;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i++] != ' ')
			only_space = 0;
	}
	if (line[0] == '\n' || only_space)
	{
		free(line);
		ft_putendl_fd(RED"Error"END, 2);
		ft_putendl_fd("Empty line Detected AFTER the map !!!", 2);
		printf(YELLOW"line number :%d\n"END, cfg->nbr_line);
		exit_free(cfg, NULL, NULL, NULL);
	}
	add_map_line(cfg, line);
}

int	parse_file(t_assets *cfg, char *filename)
{
	int		stage;
	char	*line;

	stage = 0;
	check_map_path(cfg, filename);
	cfg->fd = open(filename, O_RDONLY);
	if (cfg->fd < 0)
		exit_free(cfg, NULL, "Could not open map_file", NULL);
	line = get_next_line(cfg->fd);
	while (line)
	{
		if (stage == 0)
			parse_config_section(cfg, &stage, line);
		else
			parse_map_section(cfg, line);
		free(line);
		line = get_next_line(cfg->fd);
		cfg->nbr_line++;
	}
	close(cfg->fd);
	cfg->fd = -1;
	normalize_map(cfg);
	validate_map(cfg);
	rm_lst_spc_map(cfg);
	return (0);
}
