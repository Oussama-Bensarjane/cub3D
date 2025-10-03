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

static void	init_config(t_game *game, t_assets *assets)
{
	t_config	*config;
	int			i;

	config = &game->config;
	config->map = assets->map;
	config->map_height = assets->map_height;
	config->map_width = malloc(config->map_height * sizeof(int));
	if (!config->map_width)
		game_over(game, \
"Error: Failed to init_config [cannot mallocated config->map_width]!", EXIT_FAILURE);
	i = -1;
	while (++i < config->map_height)
		config->map_width[i] = (int)ft_strlen(config->map[i]);
	game->img.img = NULL;
	game->win = NULL;
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
		exit_free(assets, "Error: Cannot initialize Cub3D!");
	if (!assets->map)
		exit_free(assets, "Error: Cannot load the map!");
	init_config(game, assets);
	init_player(&game->player, assets);
	game->mlx = mlx_init();
	if (!game->mlx)
		game_over(game, "Error: Failed to initialize mlx!", EXIT_FAILURE);
	init_load_textures(game, assets->textures);
	init_load_weapons(game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		game_over(game, "Error: mlx_new_window failed!", EXIT_FAILURE);
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		game_over(game, "Error: mlx_new_image failed!", EXIT_FAILURE);
	game->img.data = mlx_get_data_addr(game->img.img, &game->img.bpp, \
					&game->img.size_line, &game->img.endian);
	if (!game->img.data)
		game_over(game, "Error: mlx_get_data_addr failed!", EXIT_FAILURE);
	game->config.ceiling = convert_color(assets->ceiling, game->img.endian);
	game->config.floor = convert_color(assets->floor, game->img.endian);
	if (game->config.floor == CLR_WALL)
		game->config.minimap_floor = CLR_FREE_SPACE;
	else
		game->config.minimap_floor = game->config.floor;
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
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
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
