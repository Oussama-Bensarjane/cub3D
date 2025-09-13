#include "cub3d.h"

static int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' ||
            c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_map(t_config *cfg)
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