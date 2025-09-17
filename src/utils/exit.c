#include "cub3d.h"

void	exit_failure(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

#if defined(__linux__)

void	game_over(t_game *game, char *msg, int exit_status)
{
	char	**ptr;

	if (!game)
		exit(EXIT_FAILURE);
	if (game->map)
	{
		ptr = game->map;
		while (*ptr)
			free(*ptr++);
		free(game->map);
	}
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

#elif defined(__APPLE__)

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
		free(game->mlx);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}
#endif
