#include "cub3d_bonus.h"

static void	draw_square_circle_mask(int sx, int sy,
			int color, t_game *game)
{
	t_circle	*circle;

	circle = &game->minimap.circle;
	circle->y = 0;
	while (circle->y < MINIMAP_SCALE)
	{
		circle->x = 0;
		while (circle->x < MINIMAP_SCALE)
		{
			circle->dx = (sx + circle->x) - circle->cx;
			circle->dy = (sy + circle->y) - circle->cy;
			if (circle->dx * circle->dx + circle->dy * circle->dy \
				<= circle->radius2)
				put_pixel(sx + circle->x, sy + circle->y, color, game);
			circle->x++;
		}
		circle->y++;
	}
}

static int	get_cell_color(int mx, int my, t_game *game)
{
	t_config	*config;

	config = &game->config;
	if (my < 0 || my >= config->map_height)
			return (CLR_OUTBOUND);
	else if (mx < 0 || mx >= config->map_width[my])
			return (CLR_OUTBOUND);
	if (config->map[my][mx] == '1')
			return (CLR_WALL);
	else if (config->map[my][mx] == '0')
			return (config->minimap_floor);
	return (CLR_OUTBOUND);
}

void	draw_circle_outline(t_game *game, int color)
{
	t_circle	*circle;
	int			dist2;

	circle = &game->minimap.circle;
	circle->y = -circle->radius;
	while (circle->y <= circle->radius)
	{
		circle->x = -circle->radius;
		while (circle->x <= circle->radius)
		{
			circle->dx = circle->x;
			circle->dy = circle->y;
			dist2 = circle->dx * circle->dx + circle->dy * circle->dy;
			if (dist2 <= circle->radius2 && dist2 >= circle->radius2_inner)
				put_pixel(circle->cx + circle->x, circle->cy + circle->y, color, game);
			circle->x++;
		}
		circle->y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	*minimap;

	minimap = &game->minimap;
	minimap->px = game->player.p.x / BLOCK;
	minimap->py = game->player.p.y / BLOCK;
	minimap->base_x = minimap->px - MINIMAP_RADIUS;
	minimap->base_y = minimap->py - MINIMAP_RADIUS;
	minimap->target_x = minimap->px + MINIMAP_RADIUS;
	minimap->target_y = minimap->py + MINIMAP_RADIUS;
	minimap->my = minimap->base_y;
	while (minimap->my <= minimap->target_y)
	{
		minimap->mx = minimap->base_x;
		while (minimap->mx <= minimap->target_x)
		{
			draw_square_circle_mask(
				(minimap->mx -  minimap->base_x) * MINIMAP_SCALE + MINIMAP_OFFSET_X,
				(minimap->my -  minimap->base_y) * MINIMAP_SCALE + MINIMAP_OFFSET_Y,
				get_cell_color(minimap->mx, minimap->my, game),
				game);
			minimap->mx++;
		}
		minimap->my++;
	}
}
