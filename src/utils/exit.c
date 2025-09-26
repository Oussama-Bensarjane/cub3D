#include "cub3d.h"

void	exit_failure(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void    free_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;

	if (game->config.no.ptr)
		mlx_destroy_image(game->mlx, game->config.no.ptr);
	if (game->config.so.ptr)
		mlx_destroy_image(game->mlx, game->config.so.ptr);
	if (game->config.we.ptr)
		mlx_destroy_image(game->mlx, game->config.we.ptr);
	if (game->config.ea.ptr)
		mlx_destroy_image(game->mlx, game->config.ea.ptr);
}

#if defined(__linux__)

void	game_over(t_game *game, char *msg, int exit_status)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (!game)
		exit(EXIT_FAILURE);
	free_textures(game);
	if (game->config.map)
		free_2d_array(game->config.map);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(exit_status);
}

#elif defined(__APPLE__)

void	game_over(t_game *game, char *msg, int exit_status)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (!game)
		exit(EXIT_FAILURE);
	free_textures(game);
	if (game->config.map)
		free_2d_array(game->config.map);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	exit(exit_status);
}
#endif
