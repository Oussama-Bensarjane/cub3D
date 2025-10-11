#include "cub3d.h"

char	*ft_strdup_trimnl(char *s)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len > 0 && s[len -1] == '\n')
		len--;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0] || line[0] == '\n')
		return (0);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW \n", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	check_map_path(t_assets *cfg, char *map_path)
{
	size_t	file_nm_len;
	int		fd;
	char	*tmp;

	if (!map_path)
		return ;
	tmp = ft_strrchr(map_path, '/');
	if (tmp)
	{
		if (tmp[1] == '.')
			exit_free(cfg, NULL, "Hidden files not allowed, Should be <map>.cub");
	}
	else if (map_path[0] == '.')
		exit_free(cfg, NULL, "Hidden files not allowed, Should be <map>.cub");
	file_nm_len = ft_strlen(map_path);
	if (file_nm_len <= 4
		|| ft_strncmp(map_path + file_nm_len - 4, ".cub", 3) != 0)
		exit_free(cfg, NULL, "Invalid map extension, Should be <map>.cub");
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		exit_free(cfg, NULL, "Could not open Map file");
	close(fd);
}

int	has_adjacent_space(char **map, int y, int x)
{
	return (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ');
}