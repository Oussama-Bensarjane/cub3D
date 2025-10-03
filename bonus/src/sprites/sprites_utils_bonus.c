#include "cub3d_bonus.h"

void	make_path(char *dst, const char *base, int index)
{
	int	i;

	i = 0;
	while (base[i])
	{
		dst[i] = base[i];
		i++;
	}
	dst[i++] = '/';
	if (index >= 10)
		dst[i++] = '0' + (index / 10);
	dst[i++] = '0' + (index % 10);
	dst[i++] = '.';
	dst[i++] = 'x';
	dst[i++] = 'p';
	dst[i++] = 'm';
	dst[i] = '\0';
}
