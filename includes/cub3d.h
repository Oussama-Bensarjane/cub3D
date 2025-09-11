#ifndef CUB3D_H
#define CUB3D_H

#include "libft.h"
#include "mlx.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "config.h"

// utils/exit.c
void	exit_failure(char *msg);
void	game_over(t_game *game, char *msg, int exit_status);

// gameplay/player.c
void	init_player(t_player *player);
int		key_release(int keycode, t_player *player);
int		key_press(int keycode, t_game *game);
void	move_player(t_game *game);

// gameplay/utils.c
void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);
float	fixed_distance(float x1, float y1, float x2, float y2, t_game *game);
bool	touch(float px, float py, t_game *game);

// gameplay/gameplay.c
int		draw_loop(t_game *game);

#endif
