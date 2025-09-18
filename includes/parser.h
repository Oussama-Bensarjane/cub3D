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
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_config;

// parse_map
int		parse_file(t_config *cfg, char *filename);
void	add_map_line(t_config *cfg, char *line);
void	normalize_map(t_config *cfg);
void	rm_lst_spc_map(t_config *cfg);
int		validate_map(t_config *cfg);
char	*ft_strdup_trimnl(char *s);
int		is_map_line(char *line);
int		is_valid_map_char(char c);
void	check_map_path(t_config *cfg, char *map_path);

// parse_config
int		parse_config_line(t_config *cfg, char *line);
int		strict_color(char *color);
void	validate_config(t_config *cfg, char *line);
int		check_texture_path(t_config *cfg, char *path);

// parse_utils
char	**ft_split_set(char const *s, char *seps);

// free
void	cleanup(t_config *cfg);
void	exit_free(t_config *cfg, char *msg);
void	free_config(t_config *cfg);
void	free_2d_array(char **arr);

#endif
