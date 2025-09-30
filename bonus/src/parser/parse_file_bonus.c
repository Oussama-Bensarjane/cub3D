#include "cub3d_bonus.h"

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
	if (line[0] == '\n')
		exit_free(cfg, "Error: Empty line INSIDE or AFTER the map");
	if (!is_map_line(line))
		exit_free(cfg, "Error: Invalid line after THE MAP");
	add_map_line(cfg, line);
}

// stage = 0: 0 = config, 1 = map
int	parse_file(t_assets *cfg, char *filename)
{
	int		fd;
	int		stage;
	char	*line;

	stage = 0;
	check_map_path(cfg, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_free(cfg, "Could not open map_file");
	line = get_next_line(fd);
	while (line)
	{
		if (stage == 0)
			parse_config_section(cfg, &stage, line);
		else
			parse_map_section(cfg, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	normalize_map(cfg);
	validate_map(cfg);
	rm_lst_spc_map(cfg);
	return (0);
}
