#include "cub3d_bonus.h"

static void	draw_square_circle_mask(t_game *game, int sx, int sy,
				int color)
{
	int x, y, dx, dy;
	int radius = MINIMAP_RADIUS * MINIMAP_SCALE;
	int cx = MINIMAP_OFFSET_X + radius;
	int cy = MINIMAP_OFFSET_Y + radius;

	y = 0;
	while (y < MINIMAP_SCALE)
	{
		x = 0;
		while (x < MINIMAP_SCALE)
		{
			dx = (sx + x) - cx;
			dy = (sy + y) - cy;
			if (dx * dx + dy * dy <= radius * radius)
				put_pixel(sx + x, sy + y, color, game);
			x++;
		}
		y++;
	}
}

static int      get_cell_color(t_game *game, int mx, int my)
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
	int x, y, dx, dy, dist2, r2, r2_inner;
	int radius = MINIMAP_RADIUS * MINIMAP_SCALE;
	int cx = MINIMAP_OFFSET_X + radius;
	int cy = MINIMAP_OFFSET_Y + radius;

	r2 = radius * radius;
	r2_inner = (radius - 1) * (radius - 1);
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			dx = x;
			dy = y;
			dist2 = dx * dx + dy * dy;
			if (dist2 <= r2 && dist2 >= r2_inner)
				put_pixel(cx + x, cy + y, color, game);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	int	px;
	int	py;
	int	mx;
	int	my;
	int	color;
	int	base_x;
	int	base_y;

	px = game->player.p.x / BLOCK;
	py = game->player.p.y / BLOCK;
	base_x = px - MINIMAP_RADIUS;
	base_y = py - MINIMAP_RADIUS;
	my = base_y;
	while (my <= py + MINIMAP_RADIUS)
	{
		mx = base_x;
		while (mx <= px + MINIMAP_RADIUS)
		{
			color = get_cell_color(game, mx, my);
			draw_square_circle_mask(game,
					(mx - base_x) * MINIMAP_SCALE + MINIMAP_OFFSET_X,
					(my - base_y) * MINIMAP_SCALE + MINIMAP_OFFSET_Y,
					color);
			mx++;
		}
		my++;
	}
}
