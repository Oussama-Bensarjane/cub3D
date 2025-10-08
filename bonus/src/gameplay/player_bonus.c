#include "cub3d_bonus.h"

/*
** Initialize player position, direction, and movement state
**
** - Places player at map coordinates from config, centered in map cell
** - Sets initial viewing angle according to starting direction:
**     'N' → facing up   (angle = -PI/2)
**     'S' → facing down (angle =  PI/2)
**     'E' → facing right(angle =  0)
**     'W' → facing left (angle =  PI)
**     else -> 0 // default fallback
** - Configures movement speed, rotation speed, and resets input flags
*/
void	init_player(t_player *player, t_assets *assets)
{
	if (!player || !assets)
		return ;
	player->p.x = (assets->player_x + 0.5) * BLOCK;
	player->p.y = (assets->player_y + 0.5) * BLOCK;
	if (assets->player_dir == 'N')
		player->angle = (3 * PI) / 2;
	else if (assets->player_dir == 'S')
		player->angle = PI / 2;
	else if (assets->player_dir == 'E')
		player->angle = 0;
	else if (assets->player_dir == 'W')
		player->angle = PI;
	else
		player->angle = 0;
	player->speed = 4;
	player->angle_speed = (FOV / WIDTH) + 0.01;
	player->key[KEY_UP] = false;
	player->key[KEY_DOWN] = false;
	player->key[KEY_LEFT] = false;
	player->key[KEY_RIGHT] = false;
	player->key[KEY_ROT_LEFT] = false;
	player->key[KEY_ROT_RIGHT] = false;
	player->key[KEY_V] = false;
}

static void	handle_movement_keys(int keycode, t_player *p)
{
	if (keycode == W)
		p->key[KEY_UP] = true;
	else if (keycode == S)
		p->key[KEY_DOWN] = true;
	else if (keycode == A)
		p->key[KEY_LEFT] = true;
	else if (keycode == D)
		p->key[KEY_RIGHT] = true;
	else if (keycode == LEFT)
		p->key[KEY_ROT_LEFT] = true;
	else if (keycode == RIGHT)
		p->key[KEY_ROT_RIGHT] = true;
	else if (keycode == V)
		p->key[KEY_V] = true;
}

static void	handle_action_keys(int keycode, t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (keycode == SPACE)
		trigger_attack(&game->sprite);
	else if (keycode == NUM_1)
		game->sprite.current = W_HAND;
	else if (keycode == NUM_2)
		game->sprite.current = W_PISTOL;
	else if (keycode == NUM_3)
		game->sprite.current = W_SHUTGUN;
	else if (keycode == E)
		try_toggle_door(game);
	else if (keycode == SPEEDUP && p->speed < SPEED_MAX)
		p->speed += 1;
	else if (keycode == SPEEDDOWN && p->speed > 1)
		p->speed -= 1;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		game_over(game, NULL, EXIT_SUCCESS);
	else
	{
		handle_movement_keys(keycode, &game->player);
		handle_action_keys(keycode, game);
	}
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key[KEY_UP] = false;
	else if (keycode == S)
		player->key[KEY_DOWN] = false;
	else if (keycode == A)
		player->key[KEY_LEFT] = false;
	else if (keycode == D)
		player->key[KEY_RIGHT] = false;
	else if (keycode == LEFT)
		player->key[KEY_ROT_LEFT] = false;
	else if (keycode == RIGHT)
		player->key[KEY_ROT_RIGHT] = false;
	else if (keycode == V)
		player->key[KEY_V] = false;
	return (0);
}
