#include "cub3d.h"

void	init_player(t_player *player)
{
	if (!player)
		return ;
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->speed = 4;
	player->angle_speed = FOV / WIDTH;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == ESC)
		game_over(game, NULL, EXIT_SUCCESS);
	else if (keycode == W)
		player->key_up = true;
	else if (keycode == S)
		player->key_down = true;
	else if (keycode == A)
		player->key_left = true;
	else if (keycode == D)
		player->key_right = true;
	else if (keycode == LEFT)
		player->left_rotate = true;
	else if (keycode == RIGHT)
		player->right_rotate = true;
	else if (keycode == SPEEDUP && player->speed < SPEED_MAX)
		player->speed += 1;
	else if (keycode == SPEEDDOWN && player->speed > 1)
		player->speed -= 1;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

/**
 * can_move
 * Checks if the player can move to (new_x, new_y) without colliding with walls.
 * Adds a "radius" to avoid clipping through corners.
 */
static bool	can_move(double new_x, double new_y, t_game *game)
{
	double	radius;

	radius = 5.0;
	if (touch(new_x, new_y, game))
		return (false);
	else if (touch(new_x - radius, new_y, game))
		return (false);
	else if (touch(new_x + radius, new_y, game))
		return (false);
	else if (touch(new_x, new_y - radius, game))
		return (false);
	else if (touch(new_x, new_y + radius, game))
		return (false);
	return (true);
}

void	update_position(t_player *player, t_game *game,
		double new_x, double new_y)
{
	if (can_move(new_x, new_y, game))
	{
		player->x = new_x;
		player->y = new_y;
	}
	else
	{
		if (can_move(new_x, player->y, game))
			player->x = new_x;
		if (can_move(player->x, new_y, game))
			player->y = new_y;
	}
}
