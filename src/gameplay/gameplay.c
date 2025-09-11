# include "cub3d.h"

/**
 * draw_line
 * Casts a single ray from the player and draws a vertical slice of the wall.
 *
 * @param player   Pointer to the player struct (position & angle)
 * @param game     Pointer to the game struct (map, buffer, ...)
 * @param start_x  Angle of the current ray relative to the player
 * @param i        X-coordinate (column) on the screen where the slice is drawn
 */
static void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;

	// Step 1: Cast the ray until it touches a wall
	while(!touch(ray_x, ray_y, game))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	// Step 2: Calculate distance to the wall, correcting for fish-eye effect
	// Taller slice for closer walls, shorter for farther walls
	dist = fixed_distance(player->x, player->y, ray_x, ray_y, game);
	height = (BLOCK / dist) * (WIDTH / 2);

	// Step 4: Compute vertical start/end positions for drawing
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;

	// Step 5: Draw the vertical wall slice column
	while(start_y < end)
	{
		// I can see you Mr. Texture
		put_pixel(i, start_y,  0x00FF00, game);
		start_y++;
	}
}

/**
 * draw_loop
 * Main rendering loop called every frame.
 *
 * Steps:
 *   1. Update player position based on pressed keys.
 *   2. Clear the screen buffer.
 *   3. Cast rays for each vertical column on screen and draw wall slices.
 *   4. Push the final image to the window.
 *
 * @param game  Pointer to the game structure (player, map, image, etc.)
 * @return 0   Standard return for MLX loop hook
 */
int draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;

	// Step 1: Update player movement based on input
	move_player(game);

	// Step 2: Clear the image buffer before drawing the new frame
	clear_image(game);

	// Step 3: Prepare raycasting
	fraction = FOV_R / WIDTH;         // Field of view = 60° (PI/3), split by screen width
	start_x = player->angle - (FOV_R / 2); // Start angle = center player angle - half FOV

	// Step 4: Cast rays for each column and draw walls
	i = 0;
	while(i < WIDTH)
	{
		draw_line(player, game, start_x, i); // Draw wall slice for this column
		start_x += fraction;                 // Move to next ray angle
		i++;
	}

	// Step 5: Display the final image on the window
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
