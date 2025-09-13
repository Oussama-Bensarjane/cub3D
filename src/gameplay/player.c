# include "cub3d.h"

/**
 * init_player
 * Initializes the player at cpecific position of the screen with default values.
 */
void	init_player(t_player *player)
{
	if (!player)
		return ;
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2; // Facing "upwards" for NO, etc.
	player->speed = SPEED;
	player->angle_speed = FOV / WIDTH;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

/**
 * key_press
 * Handles key press events, updating player state accordingly.
 * Special case: ESC exits the game.
 */
int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if(keycode == ESC)
		game_over(game, NULL, EXIT_SUCCESS);
	else if(keycode == W)
		player->key_up = true;
	else if(keycode == S)
		player->key_down = true;
	else if(keycode == A)
		player->key_left = true;
	else if(keycode == D)
		player->key_right = true;
	else if(keycode == LEFT)
		player->left_rotate = true;
	else if(keycode == RIGHT)
		player->right_rotate = true;
	else if(keycode == SPEEDUP && player->speed < 10)
		player->speed += 1;
	else if(keycode == SPEEDDOWN && player->speed > 1)
		player->speed -= 1;
	return (0);
}

/**
 * key_release
 * Handles key release events, resetting movement/rotation flags.
 */
int	key_release(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_up = false;
	if(keycode == S)
		player->key_down = false;
	if(keycode == A)
		player->key_left = false;
	if(keycode == D)
		player->key_right = false;
	if(keycode == LEFT)
		player->left_rotate = false;
	if(keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

/**
 * can_move
 * Checks if the player can move to (new_x, new_y) without colliding with walls.
 * Adds a "radius" to avoid clipping through corners.
 */
static bool	can_move(float new_x, float new_y, t_game *game)
{
	int	radius;

	radius = 5;
	if (touch(new_x - radius, new_y, game))
		return (false);
	if (touch(new_x + radius, new_y, game))
		return (false);
	if (touch(new_x, new_y - radius, game))
		return (false);
	if (touch(new_x, new_y + radius, game))
		return (false);
	return (true);
}

/**
 * move_player
 * Updates player position and angle based on pressed keys.
 * Handles:
 *   - Forward/backward movement (W, S)
 *   - Strafing (A, D)
 *   - Rotation (LEFT, RIGHT)
 * Also ensures player cannot walk through walls.
 */
void	move_player(t_game *game)
{
	t_player	*player;
	float		new_x;
	float		new_y;
	float		cos_angle;
	float		sin_angle;

	player = &game->player;
	new_x = player->x;
	new_y = player->y;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= player->angle_speed;
	if (player->right_rotate)
		player->angle += player->angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up)
	{
		new_x += cos_angle * player->speed;
		new_y += sin_angle * player->speed;
	}
	if (player->key_down)
	{
		new_x -= cos_angle * player->speed;
		new_y -= sin_angle * player->speed;
	}
	if (player->key_left)
	{
		new_x += sin_angle * player->speed;
		new_y -= cos_angle * player->speed;
	}
	if (player->key_right)
	{
		new_x -= sin_angle * player->speed;
		new_y += cos_angle * player->speed;
	}
	if (can_move(new_x, new_y, game))
	{
		player->x = new_x;
		player->y = new_y;
	}
}
