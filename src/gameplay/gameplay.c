#include "cub3d.h"

int	draw_loop(t_game *game)
{
	t_player			*player;
	static const double	fov = FOV * (PI / 180);
	static const double	fraction = fov / WIDTH;
	double				start_x;
	int					i;

	player = &game->player;
	move_player(game);
	clear_image(game);
	start_x = player->angle - (fov / 2);
	i = 0;
	while (i < WIDTH)
	{
		raycaster(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
