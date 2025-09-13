#include "cub3d.h"

void	add_map_line(t_config *cfg, char *line)
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

void normalize_map(t_config *cfg)
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

void	rm_lst_spc_map(t_config *cfg)
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