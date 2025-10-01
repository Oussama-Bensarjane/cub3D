#include "cub3d_bonus.h"

/* small filled circle (player dot) */
static void     draw_filled_circle_minimap(int cx, int cy, int radius, int color, t_game *game)
{
	int	dx;
	int	dy;

	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if ((dx * dx) + (dy * dy) <= (radius * radius))
				put_pixel(cx + dx, cy + dy, color, game);
			dx++;
		}
		dy++;
	}
}

/* Bresenham integer line */
static void	draw_minimap_line(int x0, int y0, int x1, int y1, int color, t_game *game)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	dy = -abs(y1 - y0);
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
		put_pixel(x0, y0, color, game);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_minimap_player(t_game *game)
{
		t_player			*player;
		static const double	fov = FOV * (PI / 180);
		static const double	fraction = fov / WIDTH;
		static const int	center_px = MINIMAP_OFFSET_X + (MINIMAP_SCALE * MINIMAP_RADIUS) + (MINIMAP_SCALE / 2);
		static const int	center_py = MINIMAP_OFFSET_Y + (MINIMAP_SCALE * MINIMAP_RADIUS) + (MINIMAP_SCALE / 2);
		int					dot_r;
		double				end;
		double				i;

		player = &game->player;
		if (MINIMAP_SCALE <= 3)
			dot_r = 1;
		else
			dot_r = MINIMAP_SCALE / 2;
		draw_filled_circle_minimap(center_px, center_py, dot_r, CLR_PLAYER, game);
		end = player->angle + (PI/6);
		i = player->angle - (PI/6);
		while (i < end)
		{
			draw_minimap_line(center_px, center_py,
				round(center_px + (cos(i) * dot_r)),
				round(center_py + (sin(i) * dot_r)),
				game->config.minimap_floor, \
				game);
			i+=fraction;
		}
}
