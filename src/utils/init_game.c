#include "cub3d.h"

static void	add_door(t_game *game, int x, int y)
{
	t_door	*door;
	int		s;

	door = malloc(sizeof(t_door));
	if (!door)
		game_over(game, "Error: Failed to malloc door!", EXIT_FAILURE);
	door->x = x;
	door->y = y;
	door->is_open = 0;
	s = x + y;
	door->id = (s * (s + 1)) / 2 + y;
	ft_lstadd_back(&game->doors, ft_lstnew(door));
}

static void	init_config(t_game *game, t_assets *assets)
{
	t_config	*config;
	int			i;
	int			j;

	config = &game->config;
	config->map = assets->map;
	config->map_height = assets->map_height;
	config->map_width = malloc(config->map_height * sizeof(int));
	if (!config->map_width)
		game_over(game,
			"Error: Failed to init_config [malloc config->map_width]!",
			EXIT_FAILURE);
	game->doors = NULL;
	i = -1;
	while (++i < config->map_height)
	{
		config->map_width[i] = (int)ft_strlen(config->map[i]);
		j = -1;
		while (++j < config->map_width[i])
		{
			if (config->map[i][j] == 'D')
				add_door(game, j, i);
		}
	}
}

static void	init_ceiling_floor_colors(t_game *game, t_assets *assets)
{
	int	*floor;

	game->config.ceiling = convert_color(assets->ceiling, game->img.endian);
	floor = &game->config.floor;
	*floor = convert_color(assets->floor, game->img.endian);
	if (*floor == CLR_WALL || *floor == CLR_PLAYER
		|| *floor == CLR_DOOR || *floor == CLR_DOOR_AREA)
		game->config.minimap_floor = CLR_FREE_SPACE;
	else
		game->config.minimap_floor = game->config.floor;
}

static void	init_minimap(t_game *game)
{
	t_minimap	*minimap;
	t_circle	*circle;

	minimap = &game->minimap;
	circle = &game->minimap.circle;
	minimap->scale = WIDTH / 64;
	minimap->radius = minimap->scale / 2;
	minimap->radius2 = minimap->radius * minimap->radius;
	minimap->pacman.x = MINIMAP_OFFSET_X + (minimap->scale * MINIMAP_RADIUS) \
														+ (minimap->scale / 2);
	minimap->pacman.y = MINIMAP_OFFSET_Y + (minimap->scale * MINIMAP_RADIUS) \
														+ (minimap->scale / 2);
	circle->radius = MINIMAP_RADIUS * game->minimap.scale;
	circle->radius2 = circle->radius * circle->radius;
	circle->radius2_inner = (circle->radius - 1) * (circle->radius - 1);
	circle->center.x = MINIMAP_OFFSET_X + circle->radius;
	circle->center.y = MINIMAP_OFFSET_Y + circle->radius;
}

void	init_game(t_game *game, t_assets *assets)
{
	if (!game)
		exit_free(assets, NULL, "Error: Cannot initialize Cub3D!", NULL);
	if (!assets->map)
		exit_free(assets, NULL, "Error: Cannot load the map!", NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_free(assets, NULL, "Failed to initialize mlx!", NULL);
	game->win = NULL;
	game->img.img = NULL;
	init_config(game, assets);
	init_player(&game->player, assets);
	init_load_textures_and_sprites(game, assets->textures);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		game_over(game, "Error: mlx_new_window failed!", EXIT_FAILURE);
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		game_over(game, "Error: mlx_new_image failed!", EXIT_FAILURE);
	game->img.data = mlx_get_data_addr(game->img.img, &game->img.bpp, \
					&game->img.size_line, &game->img.endian);
	if (!game->img.data)
		game_over(game, "Error: mlx_get_data_addr failed!", EXIT_FAILURE);
	init_ceiling_floor_colors(game, assets);
	init_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
