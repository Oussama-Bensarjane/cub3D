#include "cub3d.h"

static void	init_config(t_assets *cfg)
{
	cfg->tex_no = NULL;
	cfg->tex_so = NULL;
	cfg->tex_we = NULL;
	cfg->tex_ea = NULL;
	cfg->floor = -1;
	cfg->ceiling = -1;
	cfg->map = NULL;
	cfg->map_width = 0;
	cfg->map_height = 0;
	cfg->player_x = -1;
	cfg->player_y = -1;
	cfg->player_dir = '\0';
}

/**
 * init_game
 * Initializes the game structure:
 *   - Loads the map
 *   - Initializes the player
 *   - Sets up the MLX window and image buffer
 *
 * @param game  Pointer to the game structure to initialize
 */
static void	init_game(t_game *game, t_assets *config)
{
	if (!game)
		exit_failure("Error: Cannot initialize Cub3D!");
	game->map.map = config->map;
	if (!game->map.map)
		exit_failure("Error: Cannot load the map!");
	game->map.ceiling = config->ceiling;
	game->map.floor = config->floor;
	init_player(&game->player, config);
	game->mlx = mlx_init();
	if (!game->mlx)
		game_over(game, "Error: Failed to initialize mlx!", EXIT_FAILURE);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		game_over(game, "Error: mlx_new_window failed!", EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		game_over(game, "Error: mlx_new_image failed!", EXIT_FAILURE);
	game->data = mlx_get_data_addr(
			game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
		game_over(game, "Error: mlx_get_data_addr failed!", EXIT_FAILURE);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

static int	close_win(t_game *game)
{
	game_over(game, NULL, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_assets	cfg;
	t_game		game;

	if (ac != 2)
	{
		printf("Error: usage: %s <path-to-map.cub>\n", av[0]);
		return (1);
	}
	init_config(&cfg);
	parse_file(&cfg, av[1]);
	init_game(&game, &cfg);
	mlx_hook(game.win, 17, 1L << 0, close_win, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
