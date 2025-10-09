#include "cub3d_bonus.h"

void	init_weapon(t_weapon *w, t_weapon_type type)
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

static void	load_idle(t_game *game, t_frames *f, char *path)
{
	f->count = 1;
	f->current = 0;
	f->imgs[0].img = mlx_xpm_file_to_image(game->mlx, path, \
&f->width, &f->height);
	if (!f->imgs[0].img)
		game_over(game, "Error: load idle frame", EXIT_FAILURE);
	f->imgs[0].data = mlx_get_data_addr(f->imgs[0].img, \
&f->imgs[0].bpp, &f->imgs[0].size_line, &f->imgs[0].endian);
}

static void	load_attack(t_game *game, t_frames *f, const char *base, int count)
{
	int		i;
	char	path[256];

	if (count > MAX_FRAMES)
		game_over(game, "Error: too many frames", EXIT_FAILURE);
	f->count = count;
	f->current = 0;
	i = 0;
	while (i < count)
	{
		make_path(path, base, i + 1);
		f->imgs[i].img = mlx_xpm_file_to_image(game->mlx, path, \
&f->width, &f->height);
		if (!f->imgs[i].img)
			game_over(game, "Error: load attack frame", EXIT_FAILURE);
		f->imgs[i].data = mlx_get_data_addr(f->imgs[i].img, \
&f->imgs[i].bpp, &f->imgs[i].size_line, &f->imgs[i].endian);
		if (!f->imgs[i].data)
			game_over(game, "Error: failed to get frame data", EXIT_FAILURE);
		i++;
	}
}

void	load_weapons(t_game *game)
{
	t_weapon	*w;

	w = &game->sprite.weapons[W_HAND];
	load_idle(game, &w->idle, SPRITES_PATH"/hand/1.xpm");
	load_attack(game, &w->attack, SPRITES_PATH"/hand/", HAND_ATTACK_FRAMES);
	w = &game->sprite.weapons[W_PISTOL];
	load_idle(game, &w->idle, SPRITES_PATH"/pistol/1.xpm");
	load_attack(game, &w->attack, SPRITES_PATH"/pistol/", PISTOL_ATTACK_FRAMES);
	w = &game->sprite.weapons[W_SHUTGUN];
	load_idle(game, &w->idle, SPRITES_PATH"/shotgun/1.xpm");
	load_attack(game, &w->attack, SPRITES_PATH"/shotgun/", SHOTGUN_ATTACK_FRAMES);
	game->sprite.current = W_HAND;
}
