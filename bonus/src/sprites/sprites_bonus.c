#include "cub3d_bonus.h"

static void	update_weapon_animation(t_weapon *w)
{
	if (!w)
		return ;
	w->frame_timer++;
	if (w->frame_timer < w->frame_delay)
		return ;
	w->frame_timer = 0;
	if (w->state == WS_IDLE)
		return ;
	else if (w->state == WS_ATTACK)
	{
		w->attack.current++;
		if (w->attack.current >= w->attack.count)
		{
			w->attack.current = 0;
			w->state = WS_IDLE;
		}
	}
}

void	trigger_attack(t_sprite *sprite)
{
	t_weapon	*w;

	w = &sprite->weapons[sprite->current];
	if (w->state == WS_IDLE)
	{
		w->state = WS_ATTACK;
		w->attack.current = 0;
		w->frame_timer = 0;
	}
}

void	update_sprites(t_sprite *sprite)
{
	t_weapon		*w;
	static t_weapon	*prev_w = NULL;

	w = &sprite->weapons[sprite->current];
	if (prev_w != NULL && prev_w != w)
	{
		prev_w->state = WS_IDLE;
		prev_w->attack.current = 0;
	}
	prev_w = w;
	update_weapon_animation(w);
}

static int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_weapon(t_game *game)
{
	t_frames	*f;
	t_weapon	*w;
	t_pointi	p;
	t_pointi	base;
	int			color;

	w = &game->sprite.weapons[game->sprite.current];
	if (w->state == WS_ATTACK)
		f = &w->attack;
	else
		f = &w->idle;
	if (f->count == 0)
		return ;
	base = (t_pointi){(WIDTH - f->width) / 2, HEIGHT - f->height};
	p.y = -1;
	while (++p.y < f->height)
	{
		p.x = -1;
		while (++p.x < f->width)
		{
			color = get_pixel_color(&f->imgs[f->current], p.x, p.y);
			if (color == 0x00FF00)
				continue ;
			put_pixel(base.x + p.x, base.y + p.y, color, &game->img);
		}
	}
}
