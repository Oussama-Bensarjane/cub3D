#include "cub3d.h"

static int	check_part(char **parts)
{
	int		i;
	char	*part;

	i = -1;
	while (++i < 3)
	{
		part = parts[i];
		while (*part == '0' && *(part + 1))
			part++;
		if (ft_strlen(part) > 3)
			return (-1);
	}
	return (0);
}

static int	parse_color(char *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	if (strict_color(color) == -1)
		return (-1);
	parts = ft_split(color, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_2d_array(parts), -1);
	if (check_part(parts) == -1)
		return (free_2d_array(parts), -1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_2d_array(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	set_texture_color(t_assets *cfg, char **parts)
{
	size_t	len;

	len = ft_strlen(parts[0]);
	if (!ft_strncmp(parts[0], "NO", len) && !cfg->textures[TEX_NO])
		cfg->textures[TEX_NO] = ft_strdup(parts[1]);
	else if (!ft_strncmp(parts[0], "SO", len) && !cfg->textures[TEX_SO])
		cfg->textures[TEX_SO] = ft_strdup(parts[1]);
	else if (!ft_strncmp(parts[0], "WE", len) && !cfg->textures[TEX_WE])
		cfg->textures[TEX_WE] = ft_strdup(parts[1]);
	else if (!ft_strncmp(parts[0], "EA", len) && !cfg->textures[TEX_EA])
		cfg->textures[TEX_EA] = ft_strdup(parts[1]);
	else if (!ft_strncmp(parts[0], "F", len) && cfg->floor == -1)
		cfg->floor = parse_color(parts[1]);
	else if (!ft_strncmp(parts[0], "C", len) && cfg->ceiling == -1)
		cfg->ceiling = parse_color(parts[1]);
	else
		return (-1);
	return (0);
}

int	parse_config_line(t_assets *cfg, char *line)
{
	char	**parts;
	char	*trimed;

	trimed = ft_strtrim(line, " \t\n");
	if (!trimed || !trimed[0])
		return (free(trimed), 0);
	parts = ft_split_set(trimed, " \t");
	free(trimed);
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		free_2d_array(parts);
		exit_free(cfg, line, "Invalid or malformed configuration line", NULL);
	}
	if (set_texture_color(cfg, parts) == -1)
	{
		free_2d_array(parts);
		exit_free(cfg, line, "Invalid or duplicated configuration entry", NULL);
	}
	free_2d_array(parts);
	return (0);
}

int	strict_color(char *color)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	if (!color || !ft_isdigit(color[0])
		|| !ft_isdigit(color[ft_strlen(color) - 1]))
		return (-1);
	while (color[i])
	{
		if (ft_isdigit(color[i]))
			i++;
		else if (color[i] == ',')
		{
			if (++comma > 2)
				break ;
			i++;
		}
		else
			return (-1);
	}
	if (comma != 2)
		return (-1);
	return (0);
}
