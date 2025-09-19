#ifndef PARSER_H
# define PARSER_H

# define ERR_CLR "Floor/Ceiling color misconfigured\n(R,G,B) \
values must be integers in the range 0–255\nExample: F 220,100,0"

/* ===========================================================
**                     MAP PARSING
** ===========================================================
*/

/**
 * Parse the entire map file (.cub).
 * @param cfg - pointer to assets/config structure
 * @param filename - path to the .cub file
 * @return 0 on success, -1 on failure
 */
/* ---------- Map Parsing ---------- */
int   parse_file(t_assets *cfg, char *filename);
void  add_map_line(t_assets *cfg, char *line);
void  normalize_map(t_assets *cfg);
void  rm_lst_spc_map(t_assets *cfg);
int   validate_map(t_assets *cfg);
char *ft_strdup_trimnl(char *s);
int   is_map_line(char *line);
int   is_valid_map_char(char c);
void  check_map_path(t_assets *cfg, char *map_path);

/* ---------- Config Parsing ---------- */
int   parse_config_line(t_assets *cfg, char *line);
int   strict_color(char *color);
void  validate_config(t_assets *cfg, char *line);
int   check_texture_path(t_assets *cfg, char *path);

/* ---------- Utilities ---------- */
char **ft_split_set(char const *s, char *seps);

/* ---------- Cleanup ---------- */
void  cleanup(t_assets *cfg);
void  exit_free(t_assets *cfg, char *msg);
void  free_config(t_assets *cfg);
void  free_2d_array(char **arr);

#endif
