#ifndef TEXTURES_H
# define TEXTURES_H

typedef struct s_draw_line_info
{
	int		start;
	int		end;
	int		line_h;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
}	t_draw_line_info;

void		init_load_textures(t_game *game, t_assets *config);
int			get_pixel_clr(t_textures *tex, int x, int y);
t_textures	*choose_texture(t_game *game, t_ray *ray);
void		draw_ceiling(t_game *game, int x, int start_y, int end_y);
void		draw_floor(t_game *game, int x, int start_y, int end_y);

double		calc_tex_step(t_textures *texture, int line_h, int start);
void		calc_line_limits(double wall_dist, int *start,\
	int *end, int *line_h);
int			calc_tex_x(t_game *game, t_ray *ray, int text_width,\
	double wall_dist);

void		free_textures(t_game *game);

#endif
