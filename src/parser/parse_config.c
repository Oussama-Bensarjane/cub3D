#include "cub3d.h"

int parse_config_line(t_config *cfg, char *line)
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

int	strict_color(char *color)
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

int	parse_color(char *color)
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
	return ((r << 16) | (g << 8) | b);
}

void	validate_config(t_config *cfg, char *line)
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

int check_texture_path(t_config *cfg , char *path)
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
