#include "cub3d_bonus.h"

int	draw_loop(t_game *game)
{
	static const double		fov = FOV * (PI / 180);
	static const double		fraction = fov / WIDTH;
	int						i;

	move_player(game);
	clear_image(game);
	game->ray.angle = game->player.angle - (fov / 2);
	i = 0;
	while (i < WIDTH)
	{
		raycaster(i, game);
		game->ray.angle += fraction;
		i++;
	}
	draw_minimap(game);
	draw_minimap_player(game);
	draw_circle_outline(game, CLR_WHITE);
	draw_circle_outline(game, CLR_GREY);
	draw_circle_outline(game, CLR_BLACK);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
