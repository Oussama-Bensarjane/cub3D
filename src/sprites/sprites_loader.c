#include "cub3d.h"

static void	load_idle_frame(t_game *game, t_frames *f, char *path)
{
	f->count = 1;
	f->current = 0;
	f->imgs[0].img = mlx_xpm_file_to_image(game->mlx, path,
			&f->width, &f->height);
	if (!f->imgs[0].img)
	{
		printf(RED"Error\n"END"path: "YELLOW"%s\n", path);
		game_over(game, END IDLE_F, EXIT_FAILURE);
	}
	f->imgs[0].data = mlx_get_data_addr(f->imgs[0].img,
			&f->imgs[0].bpp, &f->imgs[0].size_line, &f->imgs[0].endian);
	if (!f->imgs[0].data)
	{
		printf(RED"Error\n"END"path: "YELLOW"%s\n", path);
		game_over(game, END F_DATA, EXIT_FAILURE);
	}
}

static void	load_attack_and_reload_frames(t_game *game, t_frames *f,
	const char *base, int count)
{
	int		i;
	char	path[256];

	if (count > MAX_FRAMES)
		game_over(game, "Error: too many frames", EXIT_FAILURE);
	f->count = count;
	f->current = 0;
	i = -1;
	while (++i < count)
	{
		make_path(path, base, i + 1);
		f->imgs[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&f->width, &f->height);
		if (!f->imgs[i].img)
			(printf(RED"Error\n"END"path: "YELLOW"%s\n", path),
				game_over(game, ATTK_F, EXIT_FAILURE));
		f->imgs[i].data = mlx_get_data_addr(f->imgs[i].img,
				&f->imgs[i].bpp, &f->imgs[i].size_line, &f->imgs[i].endian);
		if (!f->imgs[i].data)
		{
			printf(RED"Error\n"END"path: "YELLOW"%s\n", path);
			game_over(game, END F_DATA, EXIT_FAILURE);
		}
	}
}

void	load_weapons(t_game *game)
{
	t_weapon	*w;

	w = &game->sprite.weapons[W_HAND];
	load_idle_frame(game, &w->idle, SPRITES_PATH"/hand/1.xpm");
	load_attack_and_reload_frames(game, &w->attack,
		SPRITES_PATH"/hand", NUM_H_ATK);
	w = &game->sprite.weapons[W_PISTOL];
	load_idle_frame(game, &w->idle, SPRITES_PATH"/pistol/attack/1.xpm");
	load_idle_frame(game, &w->idle_reload, SPRITES_PATH"/pistol/reload/1.xpm");
	load_attack_and_reload_frames(game, &w->attack,
		SPRITES_PATH"/pistol/attack", NUM_P_ATK);
	load_attack_and_reload_frames(game, &w->reload,
		SPRITES_PATH"/pistol/reload", NUM_P_RELO);
	w->bullets = 0;
	w = &game->sprite.weapons[W_SHUTGUN];
	load_idle_frame(game, &w->idle, SPRITES_PATH"/shotgun/1.xpm");
	load_attack_and_reload_frames(game, &w->attack,
		SPRITES_PATH"/shotgun", NUM_SH_ATK);
	game->sprite.current = W_HAND;
}
