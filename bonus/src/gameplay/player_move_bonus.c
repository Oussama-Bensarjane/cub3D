#include "cub3d_bonus.h"

static void	update_angle(t_player *player)
{
	if (player->key[KEY_ROT_LEFT])
		player->angle -= player->angle_speed;
	else if (player->key[KEY_ROT_RIGHT])
		player->angle += player->angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	else if (player->angle < 0)
		player->angle = 2 * PI;
}

static void	move_forward_backward(t_point *new_p, t_player *player)
{
	if (player->key[KEY_UP])
	{
		new_p->x += player->cos_angle * player->speed;
		new_p->y += player->sin_angle * player->speed;
	}
	else if (player->key[KEY_DOWN])
	{
		new_p->x -= player->cos_angle * player->speed;
		new_p->y -= player->sin_angle * player->speed;
	}
}

static void	move_strafe(t_point *new_p, t_player *player)
{
	if (player->key[KEY_LEFT])
	{
		new_p->x += player->sin_angle * player->speed;
		new_p->y -= player->cos_angle * player->speed;
	}
	else if (player->key[KEY_RIGHT])
	{
		new_p->x -= player->sin_angle * player->speed;
		new_p->y += player->cos_angle * player->speed;
	}
}

static void	update_position(t_point new_p, t_game *game)
{
	if (can_move(new_p, game))
		game->player.p = new_p;
	else
	{
		if (can_move((t_point){new_p.x, game->player.p.y}, game))
			game->player.p.x = new_p.x;
		if (can_move((t_point){game->player.p.x, new_p.y}, game))
			game->player.p.y = new_p.y;
	}
}

void	move_player(t_game *game)
{
	t_player	*player;
	t_point		new_p;

	player = &game->player;
	new_p = player->p;
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	update_angle(player);
	move_forward_backward(&new_p, player);
	move_strafe(&new_p, player);
	update_position(new_p, game);
}
