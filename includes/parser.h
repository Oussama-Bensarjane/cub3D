#ifndef PARSER_H
# define PARSER_H


# define ERR_CLR "Floor/Ceiling color misconfigured\n(R,G,B) \
values must be integers in the range 0–255\nExample: F 220,100,0"
# define XPM "Should be <path/to/texture>.xpm"
# define ERR_D "The Door 'D' should be between Walls."
# define ERR_DD "NO consecutive doors are allowed in the same row or column."
# define HIDE_F "Hidden files not allowed, Should be <map>.cub"
# define INV_EX_M "Invalid map extension, Should be <map>.cub"
# define CANT_OPN_M "Could not open Map file"
# define HIDE_XPM "Hidden files not allowed, "
# define CANT_OPN_TX "Could not open texture path"
# define MALLOC_F "Malloc failed "
# define INV_TX "Invalid texture extension, "

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define END "\033[0m"

/**
 * @brief Parses the .cub configuration file.
 *
 * Reads texture paths, colors, and map layout from the given file
 * and stores them into the assets structure.
 *
 * @param cfg       Pointer to the assets structure to fill.
 * @param filename  Path to the .cub configuration file.
 * @return 0 on success, 1 on failure.
 */
int		parse_file(t_assets *cfg, char *filename);

/**
 * @brief Adds a map line to the current map layout.
 *
 * Dynamically extends the map array as new lines are read.
 *
 * @param cfg   Pointer to the assets structure containing map data.
 * @param line  The line of map content to append.
 */
void	add_map_line(t_assets *cfg, char *line);

/**
 * @brief Normalizes the map to ensure rectangular dimensions.
 *
 * Pads shorter lines with spaces to make all rows equal in width.
 *
 * @param cfg  Pointer to the assets structure containing the map.
 */
void	normalize_map(t_assets *cfg);

/**
 * @brief Removes leading/trailing empty or space-only map lines.
 *
 * Ensures the map starts and ends with meaningful content.
 *
 * @param cfg  Pointer to the assets structure containing the map.
 */
void	rm_lst_spc_map(t_assets *cfg);

/**
 * @brief Validates the entire map layout.
 *
 * Checks for closed walls, valid characters, and proper structure.
 *
 * @param cfg  Pointer to the assets structure containing the map.
 * @return 1 if valid, 0 if invalid.
 */
int		validate_map(t_assets *cfg);

/**
 * @brief Checks if a given line belongs to the map section.
 *
 * Used to distinguish map lines from configuration lines.
 *
 * @param line  The line to check.
 * @return 1 if the line is part of the map, 0 otherwise.
 */
int		is_map_line(char *line);

/**
 * @brief Verifies that a walkable cell is not adjacent to a space.
 *
 * Used to detect holes or open borders in the map.
 *
 * @param map  2D array of map characters.
 * @param y    Y-coordinate (row).
 * @param x    X-coordinate (column).
 * @return 1 if an adjacent space exists, 0 otherwise.
 */
int		has_adjacent_space(char **map, int y, int x);

/**
 * @brief Checks whether a map character is valid.
 *
 * Accepts only defined symbols (e.g. '0', '1', 'N', 'S', 'E', 'W', etc.).
 *
 * @param c  Character to test.
 * @return 1 if valid, 0 otherwise.
 */
int		is_valid_map_char(char c);

/**
 * @brief Ensures that the map path points to a valid .cub file.
 *
 * @param cfg       Pointer to the assets structure.
 * @param map_path  Path to the map file.
 */
void	check_map_path(t_assets *cfg, char *map_path);

/**
 * @brief Parses a configuration line (textures or colors).
 *
 * Determines line type and stores corresponding values in assets.
 *
 * @param cfg   Pointer to the assets structure.
 * @param line  The configuration line to parse.
 * @return 0 on success, 1 on error.
 */
int		parse_config_line(t_assets *cfg, char *line);

/**
 * @brief Parses and validates a strict RGB color string.
 *
 * Ensures the color has exactly three numeric components (0–255).
 *
 * @param color  String containing the color definition.
 * @return Encoded RGB integer on success, -1 on error.
 */
int		strict_color(char *color);

/**
 * @brief Validates that all required configuration fields are set.
 *
 * Ensures no missing textures, colors, or map data before game start.
 *
 * @param cfg   Pointer to the assets structure.
 * @param line  Current configuration line for error context.
 */
void	validate_config(t_assets *cfg, char *line);

/**
 * @brief Splits a string using multiple separator characters.
 *
 * Similar to ft_split, but accepts a set of delimiters instead of one.
 *
 * @param s      String to split.
 * @param seps   String containing all valid separator characters.
 * @return A NULL-terminated array of substrings.
 */
char	**ft_split_set(char const *s, char *seps);

/**
 * @brief Exits program with cleanup after an error during parsing.
 *
 * Frees all assets and optionally prints an error message.
 *
 * @param cfg   Pointer to the assets structure.
 * @param line  Current line buffer (freed if not NULL).
 * @param msg   Error message to display.
 * @param path  Optional path for context (freed if not NULL).
 */
void	exit_free(t_assets *cfg, char *line, char *msg, char *path);

/**
 * @brief Recursively checks that the map is fully enclosed by walls.
 *
 * Uses flood fill logic to detect open boundaries.
 *
 * @param cfg  Pointer to the assets structure.
 * @param x    Current x position in map.
 * @param y    Current y position in map.
 */
void	exit_enclosure(t_assets *cfg, int x, int y);

/**
 * @brief Frees all dynamically allocated fields in the assets structure.
 *
 * @param cfg  Pointer to the assets structure.
 */
void	free_assets(t_assets *cfg);

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * @param arr  The array to free.
 */
void	free_2d_array(char **arr);

#endif
