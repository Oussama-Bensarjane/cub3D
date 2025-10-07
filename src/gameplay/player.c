#include "cub3d.h"

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
	player->angle_speed = FOV / WIDTH;
	player->key[KEY_UP] = false;
	player->key[KEY_DOWN] = false;
	player->key[KEY_LEFT] = false;
	player->key[KEY_RIGHT] = false;
	player->key[KEY_ROT_LEFT] = false;
	player->key[KEY_ROT_RIGHT] = false;
}

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == ESC)
		game_over(game, NULL, EXIT_SUCCESS);
	else if (keycode == W)
		player->key[KEY_UP] = true;
	else if (keycode == S)
		player->key[KEY_DOWN] = true;
	else if (keycode == A)
		player->key[KEY_LEFT] = true;
	else if (keycode == D)
		player->key[KEY_RIGHT] = true;
	else if (keycode == LEFT)
		player->key[KEY_ROT_LEFT] = true;
	else if (keycode == RIGHT)
		player->key[KEY_ROT_RIGHT] = true;
	else if (keycode == SPEEDUP && player->speed < SPEED_MAX)
		player->speed += 1;
	else if (keycode == SPEEDDOWN && player->speed > 1)
		player->speed -= 1;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key[KEY_UP] = false;
	if (keycode == S)
		player->key[KEY_DOWN] = false;
	if (keycode == A)
		player->key[KEY_LEFT] = false;
	if (keycode == D)
		player->key[KEY_RIGHT] = false;
	if (keycode == LEFT)
		player->key[KEY_ROT_LEFT] = false;
	if (keycode == RIGHT)
		player->key[KEY_ROT_RIGHT] = false;
	return (0);
}

/**
 * can_move
 * Checks if the player can move to P(new_x, new_y) without colliding with walls.
 * Adds a "radius" to avoid clipping through corners.
 */
static bool	can_move(t_point p, t_game *game)
{
	if (touch(p, game))
		return (false);
	else if (touch((t_point){p.x - PLAYER_RADIUS, p.y}, game))
		return (false);
	else if (touch((t_point){p.x + PLAYER_RADIUS, p.y}, game))
		return (false);
	else if (touch((t_point){p.x, p.y - PLAYER_RADIUS}, game))
		return (false);
	else if (touch((t_point){p.x, p.y + PLAYER_RADIUS}, game))
		return (false);
	return (true);
}

void	update_position(t_point new_p, t_game *game)
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
