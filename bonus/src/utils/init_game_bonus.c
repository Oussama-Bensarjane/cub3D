#include "cub3d_bonus.h"

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
		game_over(game, "Error: Failed to init_config \
[cannot mallocated config->map_width]!", EXIT_FAILURE);
	game->doors = NULL;
	i = 0;
	while (i < config->map_height)
	{
		config->map_width[i] = (int)ft_strlen(config->map[i]);
		j = 0;
		while (j < config->map_width[i])
		{
			if (config->map[i][j] == 'D')
			{
				t_door *door = malloc(sizeof(t_door));
				door->x = j;
				door->y = i;
				door->is_open = 0;
				door->anim = 0;
				door->speed = DOOR_OPEN_CLOSE_SPEED;
				ft_lstadd_back(&game->doors, ft_lstnew(door));
			}
			j++;
		}
		i++;
	}
	game->img.img = NULL;
	game->win = NULL;
}

static void	init_ceiling_floor_colors(t_game *game, t_assets *assets)
{
	game->config.ceiling = convert_color(assets->ceiling, game->img.endian);
	game->config.floor = convert_color(assets->floor, game->img.endian);
	if (game->config.floor == CLR_WALL)
		game->config.minimap_floor = CLR_FREE_SPACE;
	else
		game->config.minimap_floor = game->config.floor;
}

static void	init_minimap_circle(t_game *game)
{
	t_circle	*circle;

	circle = &game->minimap.circle;
	circle->radius = MINIMAP_RADIUS * MINIMAP_SCALE;
	circle->radius2 = circle->radius * circle->radius;
	circle->radius2_inner = (circle->radius - 1) * (circle->radius - 1);
	circle->center.x = MINIMAP_OFFSET_X + circle->radius;
	circle->center.y = MINIMAP_OFFSET_Y + circle->radius;
}

void	init_game(t_game *game, t_assets *assets)
{
	if (!game)
		exit_free(assets, "Error: Cannot initialize Cub3D!");
	if (!assets->map)
		exit_free(assets, "Error: Cannot load the map!");
	init_config(game, assets);
	init_player(&game->player, assets);
	game->mlx = mlx_init();
	if (!game->mlx)
		game_over(game, "Error: Failed to initialize mlx!", EXIT_FAILURE);
	init_load_textures(game, assets->textures);
	init_load_weapons(game);
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
	init_minimap_circle(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
