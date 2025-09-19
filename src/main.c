#include "cub3d.h"

static void	init_config(t_assets *assets)
{
	assets->tex_no = NULL;
	assets->tex_so = NULL;
	assets->tex_we = NULL;
	assets->tex_ea = NULL;
	assets->floor = -1;
	assets->ceiling = -1;
	assets->map = NULL;
	assets->map_width = 0;
	assets->map_height = 0;
	assets->player_x = -1;
	assets->player_y = -1;
	assets->player_dir = '\0';
}

static int	convert_color(int color, int endian)
{
	int r;
	int g;
	int b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (endian == 0)
		return (r << 16) | (g << 8) | b;
	else
		return (b << 16) | (g << 8) | r;
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
static void	init_game(t_game *game, t_assets *assets)
{
	if (!game)
		exit_failure("Error: Cannot initialize Cub3D!");
	game->config.map = assets->map;
	if (!game->config.map)
		exit_failure("Error: Cannot load the map!");
	init_player(&game->player, assets);
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
	game->config.ceiling = convert_color(assets->ceiling, game->endian);
	game->config.floor = convert_color(assets->floor, game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
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
		return (1);
	}
	init_config(&assets);
	parse_file(&assets, av[1]);
	init_game(&game, &assets);
	mlx_hook(game.win, 17, 1L << 0, close_win, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
