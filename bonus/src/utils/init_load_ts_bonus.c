#include "cub3d_bonus.h"

static void	init_textures(t_texture *textures)
{
	int	i;

	i = 0;
	while (i < TEX_MAX)
	{
		textures[i].img = (t_img){NULL, NULL, 0, 0, 0};
		textures[i].width = 0;
		textures[i].height = 0;
		i++;
	}
}

static void	init_weapon(t_weapon *w, t_weapon_type type)
{
	int	i;

	i = 0;
	while (i < MAX_FRAMES)
	{
		w->idle.imgs[i].img = NULL;
		w->attack.imgs[i].img = NULL;
		i++;
	}
	w->idle.count = 0;
	w->idle.current = 0;
	w->attack.count = 0;
	w->attack.current = 0;
	w->frame_timer = 0;
	w->frame_delay = 2;
	if (type == W_SHUTGUN)
		w->frame_delay = 1;
	w->state = WS_IDLE;
}

void	init_load_textures_and_sprites(t_game *game, char *paths[TEX_MAX])
{
	t_weapon	*w;
	int			j;

	init_textures(game->config.textures);
	j = 0;
	while (j < W_MAX)
	{
		w = &game->sprite.weapons[j];
		init_weapon(w, j);
		j++;
	}
	load_textures(game, paths);
	load_weapons(game);
}
