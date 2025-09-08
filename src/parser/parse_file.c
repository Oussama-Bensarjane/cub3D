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
	// dup[len] = '\0';
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
		return ;
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

	if (!line || !*line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSWE \n", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int parse_file(t_config *cfg, char *filename)
{
	int     fd;
	int     stage;
	char    *line;

	stage = 0;  // 0 = config, 1 = map
	fd = open(filename, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (stage == 0)
		{
			if (is_map_line(line))
				stage = 1;
			// else
			// 	parse_config_line(line, cfg);
		}
		if (stage == 1 && line[0] != '\n')
			add_map_line(cfg, line);
		stage = 0;
		free(line);
	}
	close(fd);
	// validate_config(cfg);
	// validate_map(cfg);
	return (0);
}
