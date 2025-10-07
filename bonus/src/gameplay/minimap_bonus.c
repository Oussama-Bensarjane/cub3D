#include "cub3d_bonus.h"

static void	draw_square_circle_mask(int sx, int sy, int color, t_game *game)
{
	t_circle	*circle;

	circle = &game->minimap.circle;
	circle->p.y = 0;
	while (circle->p.y < MINIMAP_SCALE)
	{
		circle->p.x = 0;
		while (circle->p.x < MINIMAP_SCALE)
		{
			circle->d.x = (sx + circle->p.x) - circle->center.x;
			circle->d.y = (sy + circle->p.y) - circle->center.y;
			if (circle->d.x * circle->d.x + circle->d.y * circle->d.y \
				<= circle->radius2)
				put_pixel(sx + circle->p.x, sy + circle->p.y, color, &game->img);
			circle->p.x++;
		}
		circle->p.y++;
	}
}

static int	get_cell_color(int mx, int my, t_game *game)
{
	t_config	*config;
	char		tile;

	config = &game->config;
	if (my < 0 || my >= config->map_height)
		return (CLR_OUTBOUND);
	else if (mx < 0 || mx >= config->map_width[my])
		return (CLR_OUTBOUND);
	tile = config->map[my][mx];
	if (tile == '1')
		return (CLR_WALL);
	else if (tile == '0' || tile == 'O')
		return (config->minimap_floor);
	else if (tile == 'D')
		return (CLR_DOOR);
	return (CLR_OUTBOUND);
}

void	draw_circle_outline(t_game *game, int color)
{
	t_circle	*circle;
	int			dist2;

	circle = &game->minimap.circle;
	circle->p.y = -circle->radius;
	while (circle->p.y <= circle->radius)
	{
		circle->p.x = -circle->radius;
		while (circle->p.x <= circle->radius)
		{
			circle->d.x = circle->p.x;
			circle->d.y = circle->p.y;
			dist2 = circle->d.x * circle->d.x + circle->d.y * circle->d.y;
			if (dist2 <= circle->radius2 && dist2 >= circle->radius2_inner)
				put_pixel(circle->center.x + circle->p.x,
					circle->center.y + circle->p.y, color, &game->img);
			circle->p.x++;
		}
		circle->p.y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	*minimap;

	minimap = &game->minimap;
	minimap->p.x = game->player.p.x / BLOCK;
	minimap->p.y = game->player.p.y / BLOCK;
	minimap->base.x = minimap->p.x - MINIMAP_RADIUS;
	minimap->base.y = minimap->p.y - MINIMAP_RADIUS;
	minimap->target.x = minimap->p.x + MINIMAP_RADIUS;
	minimap->target.y = minimap->p.y + MINIMAP_RADIUS;
	minimap->map.y = minimap->base.y;
	while (minimap->map.y <= minimap->target.y)
	{
		minimap->map.x = minimap->base.x;
		while (minimap->map.x <= minimap->target.x)
		{
			draw_square_circle_mask((minimap->map.x - minimap->base.x) \
				* MINIMAP_SCALE + MINIMAP_OFFSET_X,
				(minimap->map.y - minimap->base.y) \
				* MINIMAP_SCALE + MINIMAP_OFFSET_Y,
				get_cell_color(minimap->map.x, minimap->map.y, game), game);
			minimap->map.x++;
		}
		minimap->map.y++;
	}
}
