#include "cub3d_bonus.h"

void	try_toggle_door(t_game *game)
{
	t_list		*node;
	t_door		*door;
	t_point		d;
	double		dist;

	node = game->doors;
	while (node)
	{
		door = node->content;
		d.x = (door->x + 0.5) - ((game->player.p.x + PLAYER_RADIUS) / BLOCK);
		d.y = (door->y + 0.5) - ((game->player.p.y + PLAYER_RADIUS) / BLOCK);
		dist = sqrt(d.x * d.x + d.y * d.y);
		if (dist <= 2.0 && dist > 0.5)
		{
			if (door->is_open && door->x == (game->player.p.x / BLOCK) && \
				door->y == (game->player.p.x / BLOCK))
			{
				node = node->next;
				continue ;
			}
			door->is_open = !door->is_open;
			if (door->is_open)
				game->config.map[door->y][door->x] = '0';
			else
				game->config.map[door->y][door->x] = 'D';
		}
		node = node->next;
	}
}

void	update_door(t_game *game)
{
	t_list	*node;
	t_door	*door;

	node = game->doors;
	while (node)
	{
		door = node->content;
		if (door->is_open && door->anim < 1.0)
			door->anim += door->speed;
		else if (!door->is_open && door->anim > 0.0)
			door->anim -= door->speed;
		if (door->anim > 1.0)
			door->anim = 1.0;
		if (door->anim < 0.0)
			door->anim = 0.0;
		node = node->next;
	}
}
