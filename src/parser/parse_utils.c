#include "cub3d.h"

char	*ft_strdup_trimnl(char *s)
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

int is_map_line(char *line)
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

void	check_map_path(t_config *cfg, char *map_path)
{

	size_t len;
	int fd;

	if (!map_path)
		return ;
	len = ft_strlen(map_path);
	if (len <= 4 || ft_strncmp(map_path + len - 4, ".cub", 3) != 0)
		exit_free(cfg, "Invalid map extension, Should be <map>.cub");
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		exit_free(cfg, "Could not open Map file");
	close(fd);
}