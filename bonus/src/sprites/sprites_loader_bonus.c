#include "cub3d_bonus.h"

static void	init_weapon(t_weapon *w)
{
	// Initialize idle frames
	w->idle.imgs = NULL;
	w->idle.count = 0;
	w->idle.current = 0;
	// Initialize attack frames
	w->attack.imgs = NULL;
	w->attack.count = 0;
	w->attack.current = 0;
	// Initialize weapon properties
	w->frame_timer = 0;
	w->frame_delay = 5;
	w->state = WS_IDLE;// start in idle state
}

static void	load_idle(t_game *game, t_frames *f, char *path)
{
	f->imgs = malloc(sizeof(t_img));
	if (!f->imgs)
		game_over(game, "Error: malloc idle", EXIT_FAILURE);
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

	f->imgs = malloc(sizeof(t_img) * count);
	if (!f->imgs)
		game_over(game, "Error: malloc attack", EXIT_FAILURE);
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

void	init_load_weapons(t_game *game)
{
	t_weapon	*w;

	w = &game->sprite.weapons[W_HAND];
	init_weapon(w);
	load_idle(game, &w->idle, "bonus/src/sprites/hand/1.xpm");
	load_attack(game, &w->attack, "bonus/src/sprites/hand/", 3);
	w = &game->sprite.weapons[W_PISTOL];
	init_weapon(w);
	load_idle(game, &w->idle, "bonus/src/sprites/pistol/1.xpm");
	load_attack(game, &w->attack, "bonus/src/sprites/pistol/", 5);
	w = &game->sprite.weapons[W_SHUTGUN];
	init_weapon(w);
	load_idle(game, &w->idle, "bonus/src/sprites/shutgun/1.xpm");
	load_attack(game, &w->attack, "bonus/src/sprites/shutgun/", 17);
	// load_weapon_sword(game, &game->sprite.weapons[W_SWORD]);
	game->sprite.current = W_HAND;
}
