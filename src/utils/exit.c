#include "cub3d.h"

static void	destroy_textures(t_game *game)
{
	int	i;

	if (!game || !game->mlx)
		return ;
	i = 0;
	while (i < TEX_MAX)
	{
		if (game->config.textures[i].img.img)
			mlx_destroy_image(game->mlx, game->config.textures[i].img.img);
		i++;
	}
}

#if defined(__linux__)

void	game_over(t_game *game, char *msg, int exit_status)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (!game)
		exit(EXIT_FAILURE);
	destroy_textures(game);
	if (game->config.map)
		free_2d_array(game->config.map);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
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
	destroy_textures(game);
	if (game->config.map)
		free_2d_array(game->config.map);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	exit(exit_status);
}
#endif
