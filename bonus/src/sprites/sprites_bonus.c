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
	{
		w->idle.current++;
		if (w->idle.current >= w->idle.count)
			w->idle.current = 0; // loop idle frames
	}
	else if (w->state == WS_ATTACK)
	{
		w->attack.current++;
		if (w->attack.current >= w->attack.count)
		{
			w->attack.current = 0;// reset attack animation
			w->state = WS_IDLE;// return to idle after attack
		}
	}
}

void	trigger_attack(t_sprite *sprite)
{
	t_weapon	*w;

	w = &sprite->weapons[sprite->current];
	if (w->state == WS_IDLE) // only trigger if not already attacking
	{
		w->state = WS_ATTACK;
		w->attack.current = 0;// restart attack animation from frame 0
		w->frame_timer = 0;// reset timer so animation starts fresh
	}
}

void	update_sprites(t_sprite *sprite)
{
	t_weapon	*w;

	w = &sprite->weapons[sprite->current]; // take address
	update_weapon_animation(w);
}

void	draw_weapon(t_game *game)
{
	t_weapon	*w;
	t_frames	*f;
	t_img		*img;

	w = &game->sprite.weapons[game->sprite.current];
	if (w->state == WS_ATTACK)
		f = &w->attack;
	else
		f = &w->idle;
	if (f->count == 0) // no frames loaded, avoid segfault
		return ;
	img = &f->imgs[f->current];
	mlx_put_image_to_window(game->mlx, game->win, img->img, \
(WIDTH - f->width) / 2, (HEIGHT - f->height));// center bottom
}
