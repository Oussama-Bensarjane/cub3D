#include "cub3d_bonus.h"

static void	init_assets(t_assets *assets)
{
	int	i;

	i = 0;
	while (i < TEX_MAX)
		assets->textures[i++] = NULL;
	assets->floor = -1;
	assets->ceiling = -1;
	assets->map = NULL;
	assets->map_width = 0;
	assets->map_height = 0;
	assets->player_x = -1;
	assets->player_y = -1;
	assets->player_dir = '\0';
}

static int	close_win(t_game *game)
{
	game_over(game, NULL, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_assets	assets;
	t_game		game;

	if (ac != 2)
	{
		printf("Error: usage: %s <path-to-map.cub>\n", av[0]);
		return (EXIT_FAILURE);
	}
	init_assets(&assets);
	parse_file(&assets, av[1]);
	init_game(&game, &assets);
	mlx_hook(game.win, 17, 1L << 0, close_win, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
