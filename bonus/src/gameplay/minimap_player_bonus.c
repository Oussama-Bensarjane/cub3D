#include "cub3d_bonus.h"

/* small filled circle (player dot) */
static void     draw_filled_circle_minimap(t_game *game, int cx, int cy, int radius, int color)
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
static void	draw_minimap_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
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
		t_player			*p;
		static const double	fov = FOV * (PI / 180);
		static const double	fraction = fov / WIDTH;
		static int			center_px;
		static int			center_py;
		int					dot_r;
		double				dir_x;
		double				dir_y;
		int					end_x;
		int					end_y;
		int					dir_len;
		double				i;

		p = &game->player;

		center_px = MINIMAP_OFFSET_X + (MINIMAP_SCALE * MINIMAP_RADIUS) + (MINIMAP_SCALE / 2);
		center_py = MINIMAP_OFFSET_Y + (MINIMAP_SCALE * MINIMAP_RADIUS) + (MINIMAP_SCALE / 2);

		dot_r = (MINIMAP_SCALE <= 3) ? 1 : (MINIMAP_SCALE / 2);
		draw_filled_circle_minimap(game, center_px, center_py, dot_r, CLR_PLAYER);

		/* draw direction line from that fixed center */
		dir_len = dot_r;
		i = game->player.angle - (PI/6);
		while (i < game->player.angle + (PI/6))
		{
			dir_x = cos(i);
			dir_y = sin(i);
			end_x = (int)round(center_px + dir_x * dir_len);
			end_y = (int)round(center_py + dir_y * dir_len);
			draw_minimap_line(game, center_px, center_py, end_x, end_y, CLR_FREE_SPACE);
			i+=fraction;
		}
}
