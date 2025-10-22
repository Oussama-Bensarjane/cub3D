#include "cub3d.h"

static void	check_map_char_and_player(t_assets *cfg,
	int x, int y, int *player_count)
{
	char	c;

	c = cfg->map[y][x];
	if (!is_valid_map_char(c))
	{
		ft_putendl_fd(RED"Error"END, 2);
		ft_putendl_fd("Invalid character in this line of the map:", 2);
		printf("---->(%c)<----\n"YELLOW"[%s]\n\
Located in :(x,y)(%d,%d)\n"END, c, cfg->map[y], x + 1, y + 1);
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
	bool	horizontal_wall;
	bool	vertical_wall;

	if (y == 0 || x == 0 || y == cfg->map_height - 1 || x == cfg->map_width - 1)
		exit_enclosure(cfg, x, y);
	if (has_adjacent_space(cfg->map, y, x))
	{
		ft_putendl_fd(RED"Error"END, 2);
		printf("Map open near space\n"YELLOW"%s\n%s\n%s\n"END,
			cfg->map[y - 1], cfg->map[y], cfg->map[y + 1]);
		(free_assets(cfg), exit(EXIT_FAILURE));
	}
	if (cfg->map[y][x] == 'D')
	{
		horizontal_wall = (cfg->map[y][x - 1] == '1'
				&& cfg->map[y][x + 1] == '1');
		vertical_wall = (cfg->map[y - 1][x] == '1'
				&& cfg->map[y + 1] && cfg->map[y + 1][x] == '1');
		if (!(horizontal_wall || vertical_wall))
			exit_free(cfg, NULL, ERR_D, NULL);
		else if (cfg->map[y - 1][x] == 'D'
				|| (cfg->map[y + 1] && cfg->map[y + 1][x] == 'D')
				|| cfg->map[y][x - 1] == 'D' || cfg->map[y][x + 1] == 'D')
			exit_free(cfg, NULL, ERR_D"\n"YELLOW ERR_DD END, NULL);
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
		return (exit_free(cfg, NULL, "Map is empty", NULL), -1);
	y = -1;
	while (++y < cfg->map_height)
	{
		x = -1;
		while (cfg->map[y][++x])
		{
			c = cfg->map[y][x];
			check_map_char_and_player(cfg, x, y, &player_count);
			if (c == '0' || c == 'N' || c == 'S' || c == 'E'
				|| c == 'W' || c == 'D')
				check_map_enclosure(cfg, x, y);
		}
	}
	if (player_count != 1)
		return (exit_free(cfg, NULL, "Invalid player spawn count", NULL), -1);
	return (0);
}

static void	check_texture_path(t_assets *cfg, char *path, char *line)
{
	size_t	len;
	int		fd;
	char	*tmp;

	if (!path)
		return ;
	tmp = ft_strrchr(path, '/');
	if (tmp)
	{
		if (tmp[1] == '.')
			(free(line), exit_free(cfg, NULL, HIDE_XPM XPM, path));
	}
	else if (path[0] == '.')
		(free(line), exit_free(cfg, NULL, HIDE_XPM XPM, path));
	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 3) != 0)
		(free(line), exit_free(cfg, NULL, INV_TX XPM, path));
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(line);
		exit_free(cfg, NULL, CANT_OPN_TX, path);
	}
	close(fd);
}

void	validate_config(t_assets *cfg, char *line)
{
	int	i;

	i = 0;
	if (!cfg->textures[TEX_EA] || !cfg->textures[TEX_NO]
		|| !cfg->textures[TEX_SO] || !cfg->textures[TEX_WE])
	{
		free(line);
		exit_free(cfg, NULL, "Missing some texture(s) path(s)", NULL);
	}
	if (cfg->ceiling == -1 || cfg->floor == -1)
	{
		free(line);
		exit_free(cfg, NULL, ERR_CLR, NULL);
	}
	while (i < TEX_MAX)
		check_texture_path(cfg, cfg->textures[i++], line);
}
