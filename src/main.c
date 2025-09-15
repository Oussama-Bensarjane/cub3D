#include "cub3d.h"

/*
* get_map
* Map from map.cub
*/
char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	if (!map)
		return (NULL);
	map[0] = ft_strdup("        11111111111111111111111");
	map[1] = ft_strdup("11111111100000000000001");
	map[2] = ft_strdup("11111111100000000000001");
	map[3] = ft_strdup("10000011111110100000001");
	map[4] = ft_strdup("10000000000000100111101");
	map[5] = ft_strdup("100001110000000001  101");
	map[6] = ft_strdup("100001110000000001  101");
	map[7] = ft_strdup("100000000000000001  1001");
	map[8] = ft_strdup("100000000000000001  10001");
	map[9] = ft_strdup("111111111111111111  11111");
	map[10] = NULL;
	return (map);
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
static void	init_game(t_game *game)
{
	if (!game)
		exit_failure("Error: Cannot initialize Cub3D!");
	game->map = get_map();
	if (!game->map)
		exit_failure("Error: Cannot load the map!");
	init_player(&game->player);
	game->mlx = mlx_init();
	if (!game->mlx)
		game_over(game, "Error: Failed to initialize mlx!", EXIT_FAILURE);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		game_over(game, "Error: mlx_new_window failed!", EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		game_over(game, "Error: mlx_new_image failed!", EXIT_FAILURE);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
			game_over(game, "Error: mlx_get_data_addr failed!", EXIT_FAILURE);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

static int	close_win(t_game *game)
{
	game_over(game, NULL, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int main(void)
{
	t_game	game;

	// init game
	init_game(&game);

	// hooks
	mlx_hook(game.win, 17, 1L<<0, close_win, &game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);

	// draw loop
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
