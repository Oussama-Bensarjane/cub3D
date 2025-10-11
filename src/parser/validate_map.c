#include "cub3d.h"

static void	check_map_char_and_player(t_assets *cfg, \
	int x, int y, int *player_count)
{
	char	c;

	c = cfg->map[y][x];
	if (!is_valid_map_char(c))
	{
		ft_putendl_fd(RED"Error"END, 2);
		ft_putendl_fd("Invalid character in this line of the map:", 2);
		printf("---->(%c)<----\n"YELLOW"[%s]\nLocated in :(x,y)(%d,%d)\n"END, c, cfg->map[y], x+1,y+1);
		(free_assets(cfg), exit (EXIT_FAILURE));
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		cfg->player_dir = c;
		cfg->player_x = x;
		cfg->player_y = y;
		cfg->map[y][x] = '0';
		(*player_count)++;
	}
}

static void	check_map_enclosure(t_assets *cfg, int x, int y)
{
	if (y == 0 || x == 0 || y == cfg->map_height - 1 || x == cfg->map_width - 1)
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
	if (has_adjacent_space(cfg->map, y, x))
	{
		ft_putendl_fd(RED"Error"END, 2);
		printf("Map open near space\n"YELLOW"%s\n%s\n%s\n"END, cfg->map[y-1], cfg->map[y], cfg->map[y+1]);
	(free_assets(cfg), exit (EXIT_FAILURE));
	}
}

int	validate_map(t_assets *cfg)
{
	int		player_count;
	int		x;
	int		y;
	char	c;

	player_count = 0;
	if (!cfg->map || cfg->map_height == 0)
		return (exit_free(cfg, NULL, "Map is empty"), -1);
	y = -1;
	while (++y < cfg->map_height)
	{
		x = -1;
		while (cfg->map[y][++x])
		{
			c = cfg->map[y][x];
			check_map_char_and_player(cfg, x, y, &player_count);
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				check_map_enclosure(cfg, x, y);
		}
	}
	if (player_count != 1)
		return (exit_free(cfg, NULL, "Invalid player spawn count"), -1);
	return (0);
}

void	validate_config(t_assets *cfg, char *line)
{
	if (!cfg->textures[TEX_EA] || !cfg->textures[TEX_NO] || \
		!cfg->textures[TEX_SO] || !cfg->textures[TEX_WE])
	{
		free(line);
		exit_free(cfg, NULL, "Missing texture path(s), \
IT should be the CONFIG 1st, then MAP 2nd !!!");
	}
	if (cfg->ceiling == -1 || cfg->floor == -1)
		(free(line), exit_free(cfg, NULL, ERR_CLR));
	if (check_texture_path(cfg, cfg->textures[TEX_NO])
		|| check_texture_path(cfg, cfg->textures[TEX_SO])
		|| check_texture_path(cfg, cfg->textures[TEX_WE])
		|| check_texture_path(cfg, cfg->textures[TEX_EA]))
		(free(line), exit_free(cfg, NULL, "Invalid texture path(s)"));
}

int	check_texture_path(t_assets *cfg, char *path)
{
	size_t	len;
	int		fd;
	char	*tmp;

	if (!path)
		return (-1);
	tmp = ft_strrchr(path, '/');
	if (tmp)
	{
		if (tmp[1] == '.')
			exit_free(cfg, NULL, "Hidden files not allowed, " XPM);
	}
	else if (path[0] == '.')
		exit_free(cfg, NULL, "Hidden files not allowed, " XPM);
	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 3) != 0)
		exit_free(cfg, NULL, "Invalid texture extension, " XPM);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_free(cfg, NULL, "Could not open texture path");
	close(fd);
	return (0);
}
