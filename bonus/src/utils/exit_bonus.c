#include "cub3d_bonus.h"

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

static void	destroy_sprites(t_game *game)
{
	t_weapon	*w;
	int			i;
	int			j;
	static int	attack_frames[] = {HAND_ATTACK_FRAMES,
		PISTOL_ATTACK_FRAMES, SHOTGUN_ATTACK_FRAMES};

	if (!game || !game->mlx)
		return ;
	j = 0;
	while (j < W_MAX)
	{
		w = &game->sprite.weapons[j];
		if (w->idle.imgs[0].img)
			mlx_destroy_image(game->mlx, w->idle.imgs[0].img);
		i = 0;
		while (i < attack_frames[j])
		{
			if (w->attack.imgs[i].img)
				mlx_destroy_image(game->mlx, w->attack.imgs[i].img);
			i++;
		}
		j++;
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
	destroy_sprites(game);
	ft_lstclear(&game->doors, free);
	if (game->config.map)
		free_2d_array(game->config.map);
	if (game->config.map_width)
		free(game->config.map_width);
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
	destroy_sprites(game);
	ft_lstclear(&game->doors, free);
	if (game->config.map)
		free_2d_array(game->config.map);
	if (game->config.map_width)
		free(game->config.map_width);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	exit(exit_status);
}
#endif
