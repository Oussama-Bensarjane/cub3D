#include "cub3d.h"

static int	is_player_in_door_tile(t_point *p, t_pointi *door)
{
	if ((door->x == (int)(p->x / BLOCK) && door->y == (int)(p->y / BLOCK))
		|| (door->x == (int)((p->x + PLAYER_RADIUS) / BLOCK)
			&& door->y == (int)(p->y / BLOCK))
		|| (door->x == (int)(p->x / BLOCK)
			&& door->y == (int)((p->y + PLAYER_RADIUS) / BLOCK))
		|| (door->x == (int)((p->x - PLAYER_RADIUS) / BLOCK)
			&& door->y == (int)(p->y / BLOCK))
		|| (door->x == (int)(p->x / BLOCK)
			&& door->y == (int)((p->y - PLAYER_RADIUS) / BLOCK)))
		return (1);
	return (0);
}

static void	check_and_toggle(t_game *game, t_door *door)
{
	t_point	d;

	d.x = (door->x + 0.5) - (game->player.p.x / BLOCK);
	d.y = (door->y + 0.5) - (game->player.p.y / BLOCK);
	if (d.x * d.x + d.y * d.y > 4.0)
		return ;
	if (door->is_open && is_player_in_door_tile(&game->player.p,
			&(t_pointi){door->x, door->y}))
		return ;
	door->is_open = !door->is_open;
	if (door->is_open)
		game->config.map[door->y][door->x] = 'O';
	else
		game->config.map[door->y][door->x] = 'D';
}

void	try_toggle_door(t_game *game)
{
	t_list	*node;
	t_door	*door;

	node = game->doors;
	while (node)
	{
		door = node->content;
		if (game->ray.door_hit == door->id)
		{
			check_and_toggle(game, door);
			break ;
		}
		node = node->next;
	}
}
