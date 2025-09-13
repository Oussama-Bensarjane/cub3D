#include "cub3d.h"

static char	*ft_strdup_trimnl(char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	if (len > 0 && s[len -1] == '\n')
		len--;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

static void	add_map_line(t_config *cfg, char *line)
{
	char	**new_map;
	int		i;
	int		len;

	// Allocate new array (+2: one for new line, one for NULL)
	new_map = malloc(sizeof(char *) * (cfg->map_height + 2));
	if (!new_map)
		return ;
	// copy old map lines
	if (cfg->map)
	{
		i = -1;
		while (++i < cfg->map_height)
			new_map[i]=cfg->map[i];
	}
	// deplicat and add the new line
	new_map[cfg->map_height] = ft_strdup_trimnl(line);
	if (!new_map[cfg->map_height])
		(free(new_map), exit_free(cfg, "Malloc faileed"));
	new_map[cfg->map_height + 1] = NULL;
	// free oold map container but not the content
	if (cfg->map)
		free(cfg->map);
	// replace with the new container
	cfg->map = new_map;
	cfg->map_height++;
	// update the width 
	len = ft_strlen(cfg->map[cfg->map_height - 1]);
	if (len > cfg->map_width)
		cfg->map_width = len;
}

static int is_map_line(char *line)
{
    int i;

    if (!line || !line[0] || line[0] == '\n')
        return (0); // not a map line

    i = 0;
    while (line[i])
    {
        if (!ft_strchr("01NSEW \t\n", line[i]))
            return (0); // invalid char found
        i++;
    }
    return (1); // valid map line
}

static int	strict_color(char *color)
{
	int	i;
	int	comma;
	int	nbr_count;

	i = 0;
	comma = 0;
	nbr_count = 0;
	if (!color || !ft_isdigit(color[0]) || !ft_isdigit(color[ft_strlen(color) - 1]))
		return (-1);
	while (color[i])
    {
        if (ft_isdigit(color[i]))
		{
			if (++nbr_count > 9)
				return (-1);
		}
        else if (color[i] == ',')
        {
			if (++comma > 2)
				break ;
        }
        else
			return (-1);
		i++;
    }
	if (comma != 2)
		return (-1);
	return(0);
}

static int	parse_color(char *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	if (strict_color(color) == -1)
		return(-1);
	parts = ft_split(color, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_2d_array(parts), -1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_2d_array(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);// Into...--> 0xRRGGBB
}

static int	parse_config_line(t_config *cfg, char *line)
{
	char	**parts;
	char	*trimed;
	size_t	len;

	trimed = ft_strtrim(line, " \t\n");
	if (!trimed || !trimed[0])
		return (free(trimed), 0);
	parts = ft_split_set(trimed, " \t");
	free(trimed);
	if (!parts || !parts[0] || !parts[1] || parts[2])
		return (free(line), free_2d_array(parts), exit_free(cfg, "Missed config !!!"), -1);
	len = ft_strlen(parts[0]);
	if (!ft_strncmp(parts[0], "NO", len) && !cfg->tex_no)
		cfg->tex_no = ft_strdup(parts[1]);
	else if (!ft_strncmp(parts[0], "SO", len) && !cfg->tex_so)
		cfg->tex_so = ft_strdup(parts[1]);
	else if (!ft_strncmp(parts[0], "WE", len) && !cfg->tex_we)
		cfg->tex_we = ft_strdup(parts[1]);
	else if (!ft_strncmp(parts[0], "EA", len) && !cfg->tex_ea)
		cfg->tex_ea = ft_strdup(parts[1]);
	else if (!ft_strncmp(parts[0], "F", len) && cfg->floor_color == -1)
        cfg->floor_color = parse_color(parts[1]);
    else if (!ft_strncmp(parts[0], "C", len) && cfg->ceiling_color == -1)
        cfg->ceiling_color = parse_color(parts[1]);
	else
	{
		free_2d_array(parts);
		return (free(line), exit_free(cfg, "Missed config !!!"), -1);
	}
	free_2d_array(parts);
	return (0);
}

static int check_texture_path(t_config *cfg , char *path)
{
    size_t len;
    int fd;

    if (!path)
        return (-1);
    len = ft_strlen(path);
    if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 3) != 0)
        exit_free(cfg, "Invalid texture extension, should be .xpm");

    fd = open(path, O_RDONLY);
    if (fd == -1)
        exit_free(cfg, "Could not open texture path");
    close(fd);

    return (0);
}

static void	validate_config(t_config *cfg, char *line)
{
	if (!cfg->tex_ea || !cfg->tex_no || !cfg->tex_so || !cfg->tex_we)
		free(line), exit_free(cfg, "Missing texture path(s)");
	if (cfg->ceiling_color == -1 || cfg->floor_color == -1)
		free(line), exit_free(cfg, ERR_CLR);
	if (check_texture_path(cfg, cfg->tex_no) ||
        check_texture_path(cfg, cfg->tex_so) ||
        check_texture_path(cfg, cfg->tex_we) ||
        check_texture_path(cfg, cfg->tex_ea))
        free(line), exit_free(cfg, "Invalid texture path(s)");
}
static int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' ||
            c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	validate_map(t_config *cfg)
{
    int player_count;
	int x;
	int y;
	char c;

	player_count = 0;
	if (!cfg->map || cfg->map_height == 0)
        return (exit_free(cfg, "Map is empty"), -1);
	y = -1;
    while (++y < cfg->map_height)
    {
		x = -1;
        while (cfg->map[y][++x])
        {
            c = cfg->map[y][x];
            if (!is_valid_map_char(c))
                return (exit_free(cfg, "Invalid character in map"), -1);

            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				cfg->player_dir = c;
				cfg->player_x = x;
				cfg->player_y = y;
                player_count++;
			}

            if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {

                if (y == 0 || x == 0 || y == cfg->map_height - 1 || x >= cfg->map_width - 1)
                    return (exit_free(cfg, "Map not enclosed"), -1);

                if (cfg->map[y-1][x] == ' ' || cfg->map[y+1][x] == ' ' ||
                    cfg->map[y][x-1] == ' ' || cfg->map[y][x+1] == ' ')
                    return (exit_free(cfg, "Map open near space"), -1);
            }
        }
    }
    if (player_count != 1)
        return (exit_free(cfg, "Invalid player spawn count"), -1);

    return (0);
}

static void normalize_map(t_config *cfg)
{
    char **new_map;
    int i;
    int j;
    int len;

    new_map = malloc(sizeof(char*) * (cfg->map_height + 1));
    if (!new_map)
        exit_free(cfg, "Malloc failed");
    for (i = 0; i < cfg->map_height; i++)
    {
        new_map[i] = malloc(cfg->map_width + 1);
        if (!new_map[i])
		{
			while (--i >= 0)
            	free(new_map[i]);
        	free(new_map);
            exit_free(cfg, "Malloc failed");
		}
        len = ft_strlen(cfg->map[i]);
		j = -1;
        while (++j < len)
            new_map[i][j] = cfg->map[i][j];
        while (j < cfg->map_width)
            new_map[i][j++] = ' ';
        new_map[i][cfg->map_width] = '\0';
    }
    new_map[cfg->map_height] = NULL;
    free_2d_array(cfg->map);
    cfg->map = new_map;
}

static void	rm_lst_spc_map(t_config *cfg)
{
	int		i;
	int		len;
	int		new_map_width;

	i = 0;
	new_map_width = 0;
	while (i < cfg->map_height)
	{
		len = ft_strlen(cfg->map[i]);
		while (len > 0 && cfg->map[i][len - 1] == ' ')
			len--;
		cfg->map[i][len] = '\0';
		if (len > new_map_width)
			new_map_width = len;
		i++;
	}
	cfg->map_width = new_map_width;
}

static void	check_map_path(t_config *cfg, char *map_path)
{

	size_t len;
    int fd;

    if (!map_path)
        return ;
    len = ft_strlen(map_path);
    if (len < 4 || ft_strncmp(map_path + len - 4, ".cub", 3) != 0)
        exit_free(cfg, "invalid map extension, should be .cub");

    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        exit_free(cfg, "Could not open Map file");
    close(fd);
}

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
