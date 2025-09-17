#include "cub3d.h"

/**
 * draw_line
 * Casts a single ray from the player and draws a vertical slice of the wall.
 *
 * @param player   Pointer to the player struct (position & angle)
 * @param game     Pointer to the game struct (map, buffer, ...)
 * @param start_x  Angle of the current ray relative to the player
 * @param i        X-coordinate (column) on the screen where the slice is drawn
 */
static void	draw_line(t_player *player, t_game *game, double start_x, int i)
{
	double	ray_dir_X;
	double	ray_dir_Y;
	double	perp_wall_dist;
	double	height;
	int		start_y;
	int		end;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;
	int		side;
	double	dist_proj_plane;

	ray_dir_X = cos(start_x);
	ray_dir_Y = sin(start_x);
	map_x = player->x / BLOCK;
	map_y = player->y / BLOCK;
	delta_dist_x = (ray_dir_X == 0) ? 1e30 : fabs(1 / ray_dir_X);
	delta_dist_y = (ray_dir_Y == 0) ? 1e30 : fabs(1 / ray_dir_Y);
	if (ray_dir_X < 0)
	{
		step_x = -1;
		side_dist_x = ((player->x / BLOCK) - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - (player->x / BLOCK)) * delta_dist_x;
	}
	if (ray_dir_Y < 0)
	{
		step_y = -1;
		side_dist_y = ((player->y / BLOCK) - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - (player->y / BLOCK)) * delta_dist_y;
	}
	hit = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (game->map[map_y][map_x] == '1')
			hit = 1;
	}
	if (side == 0)
		perp_wall_dist = ((map_x - (player->x / BLOCK) + (1 - step_x) / 2) / ray_dir_X) * cos(start_x - player->angle);
	else
		perp_wall_dist = ((map_y - (player->y / BLOCK) + (1 - step_y) / 2) / ray_dir_Y) * cos(start_x - player->angle);
	dist_proj_plane = WIDTH / (2 * tan(FOV * PI / 360.0));
	height = dist_proj_plane / perp_wall_dist;
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	if (start_y < 0)
		start_y = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (start_y < end)
	{
		put_pixel(i, start_y,  0x00FF00, game);
		start_y++;
	}
}

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
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
