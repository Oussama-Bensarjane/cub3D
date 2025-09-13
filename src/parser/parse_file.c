#include "cub3d.h"

int parse_file(t_config *cfg, char *filename)
{
	int     fd;
	int     stage;
	char    *line;

	stage = 0;  // 0 = config, 1 = map
	check_map_path(cfg, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
        exit_free(cfg, "Could not open map_file");
	while ((line = get_next_line(fd)))
	{
		if (stage == 0)
		{
			if (is_map_line(line))
			{
				validate_config(cfg, line);
				stage = 1;
				add_map_line(cfg, line);
			}
			else if (line[0] != '\n')
			{
				if (parse_config_line(cfg, line) == -1)
					return (-1);
			}
		}
		else if (stage == 1)
		{
			if (line[0] == '\n')
                (free(line), exit_free(cfg, "Error: empty line inside/after map"));
			if (!is_map_line(line))
                (free(line), exit_free(cfg, "Error: invalid line after map"));
			add_map_line(cfg, line);
		}
		free(line);
	}
	close(fd);
	normalize_map(cfg);
	validate_map(cfg);
	rm_lst_spc_map(cfg);
	return (0);
}
