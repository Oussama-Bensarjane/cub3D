# include "cub3d.h"

/**
 * exit_failure
 * Prints an error message to standard error and exits the program.
 *
 * @param msg  The error message to display
 */
void	exit_failure(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	game_over(t_game *game, char *msg, int exit_status)
{
	if (!game)
		exit(EXIT_FAILURE);
	if (game->map)
		free(game->map);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}
