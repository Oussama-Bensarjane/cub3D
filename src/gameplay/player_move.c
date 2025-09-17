#include "cub3d.h"

static void	update_angle(t_player *player)
{
	if (player->left_rotate)
		player->angle -= player->angle_speed;
	if (player->right_rotate)
		player->angle += player->angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	else if (player->angle < 0)
		player->angle = 2 * PI;
}

static void	move_forward_backward(t_player *player,
		double *new_x, double *new_y)
{
	if (player->key_up)
	{
		*new_x += player->cos_angle * player->speed;
		*new_y += player->sin_angle * player->speed;
	}
	if (player->key_down)
	{
		*new_x -= player->cos_angle * player->speed;
		*new_y -= player->sin_angle * player->speed;
	}
}

static void	move_strafe(t_player *player, double *new_x, double *new_y)
{
	if (player->key_left)
	{
		*new_x += player->sin_angle * player->speed;
		*new_y -= player->cos_angle * player->speed;
	}
	if (player->key_right)
	{
		*new_x -= player->sin_angle * player->speed;
		*new_y += player->cos_angle * player->speed;
	}
}

void	move_player(t_game *game)
{
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &game->player;
	new_x = player->x;
	new_y = player->y;
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	update_angle(player);
	move_forward_backward(player, &new_x, &new_y);
	move_strafe(player, &new_x, &new_y);
	update_position(player, game, new_x, new_y);
}
