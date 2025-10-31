#include "cub3d.h"

static void	attack_loop(t_weapon *w, t_weapon_type w_type)
{
	w->attack.current++;
	if (w->attack.current >= w->attack.count)
	{
		w->attack.current = 0;
		w->state = WS_IDLE;
		if (w_type == W_PISTOL)
		{
			w->bullets++;
			if (w->bullets >= G_BULL)
			{
				w->state = WS_IDLE_RELOAD;
				w->bullets = 0;
			}
		}
	}
}

void	update_weapon_animation(t_weapon *w, t_weapon_type w_type)
{
	if (!w)
		return ;
	w->frame_timer++;
	if (w->frame_timer < w->frame_delay)
		return ;
	w->frame_timer = 0;
	if (w->state == WS_IDLE || w->state == WS_IDLE_RELOAD)
		return ;
	if (w->state == WS_RELOAD && w_type == W_PISTOL)
	{
		w->reload_timer++;
		if (w->reload_timer < w->reload_delay)
			return ;
		w->reload_timer = 0;
		w->reload.current++;
		if (w->reload.current >= w->reload.count)
		{
			w->reload.current = 0;
			w->state = WS_IDLE;
		}
	}
	else if (w->state == WS_ATTACK)
		attack_loop(w, w_type);
}

t_frames	*get_weapon(t_weapon *w)
{
	if (w->state == WS_ATTACK)
		return (&w->attack);
	else if (w->state == WS_IDLE_RELOAD)
		return (&w->idle_reload);
	else if (w->state == WS_RELOAD)
		return (&w->reload);
	else
		return (&w->idle);
}

void	make_path(char *dst, const char *base, int index)
{
	int	i;

	i = 0;
	while (base[i])
	{
		dst[i] = base[i];
		i++;
	}
	dst[i++] = '/';
	if (index >= 10)
		dst[i++] = '0' + (index / 10);
	dst[i++] = '0' + (index % 10);
	dst[i++] = '.';
	dst[i++] = 'x';
	dst[i++] = 'p';
	dst[i++] = 'm';
	dst[i] = '\0';
}
