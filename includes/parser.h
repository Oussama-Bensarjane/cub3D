#ifndef PARSER_H
# define PARSER_H

typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;

	int		floor_color;
	int		ceiling_color;

	char	**map;			//2D map Array
	int		map_width;
	int		map_height;

	int		player_x;		//starting colomn position
	int		player_y;		//starting row position
	char	player_dir;		// 'N' 'S' 'W' 'E'
}	t_config;

int		parse_file(t_config *cfg, char *filename);
void	exit_free(t_config *cfg, char *msg);
void	free_config(t_config *cfg);





#endif
