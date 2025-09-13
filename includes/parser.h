#ifndef PARSER_H
# define PARSER_H

# define ERR_CLR "Floor/Ceiling color misconfigured\n(R,G,B) \
values must be integers in the range 0–255\nExample: F 220,100,0"

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

// parse_file.c
int     parse_file(t_config *cfg, char *filename);

// parse_utils.c
char    *ft_strdup_trimnl(char *s);
int     is_map_line(char *line);
void    check_map_path(t_config *cfg, char *map_path);
char	**ft_split_set(char const *s, char *seps);

// parse_config.c
int     parse_config_line(t_config *cfg, char *line);
int     strict_color(char *color);
int     parse_color(char *color);
void    validate_config(t_config *cfg, char *line);
int     check_texture_path(t_config *cfg , char *path);

// parse_map.c
void    add_map_line(t_config *cfg, char *line);
void    normalize_map(t_config *cfg);
void    rm_lst_spc_map(t_config *cfg);
int     validate_map(t_config *cfg);

// free
void	cleanup(t_config *cfg);
void	exit_free(t_config *cfg, char *msg);
void	free_config(t_config *cfg);
void	free_2d_array(char **arr);


#endif
