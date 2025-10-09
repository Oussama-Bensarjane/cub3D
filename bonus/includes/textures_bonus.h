#ifndef TEXTURES_BONUS_H
# define TEXTURES_BONUS_H

void	load_textures(t_game *game, char *paths[TEX_MAX]);
int		convert_color(int color, int endian);
int		calc_tex_x(int text_width, double wall_dist, t_game *game);
double	calc_tex_step(int text_height, int line_h, int start);
void	draw_ceiling(int x, int start_y, int end_y, t_game *game);
void	draw_wall(int x, t_game *game);
void	draw_floor(int x, int start_y, int end_y, t_game *game);
void	free_textures_paths(char *paths[TEX_MAX]);
#endif
