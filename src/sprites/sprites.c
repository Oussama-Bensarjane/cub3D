#include "cub3d.h"

void	try_reload(t_sprite *sprite)
{
	t_weapon	*w;

	w = &sprite->weapons[sprite->current];
	if (sprite->current == W_PISTOL && w->state == WS_IDLE_RELOAD)
	{
		w->state = WS_RELOAD;
		w->idle_reload.current = 0;
		w->reload.current = 0;
		w->frame_timer = 0;
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
	if (w->state == WS_IDLE_RELOAD)
	{
		w->idle_reload.current = 0;
		w->reload.current = 0;
		w->frame_timer = 0;
	}
}

static void	update_sprites(t_sprite *sprite)
{
	t_weapon		*w;
	static t_weapon	*prev_w = NULL;

	w = &sprite->weapons[sprite->current];
	if (prev_w != NULL && prev_w != w)
	{
		if (prev_w->state != WS_IDLE_RELOAD)
			prev_w->state = WS_IDLE;
		prev_w->attack.current = 0;
	}
	prev_w = w;
	update_weapon_animation(w, sprite->current);
}

static int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	draw_weapon(t_game *game)
{
	t_frames	*f;
	t_pointi	p;
	t_pointi	base;
	int			color;

	update_sprites(&game->sprite);
	f = get_weapon(&game->sprite.weapons[game->sprite.current]);
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
