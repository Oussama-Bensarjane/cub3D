#ifndef SPRITES_H
# define SPRITES_H

# define NUM_H_ATK 3
# define NUM_P_ATK 7
# define NUM_P_RELO 14
# define NUM_SH_ATK 17
# define G_BULL 3

# define IDLE_F "Failed to load idle frame"
# define F_DATA "Failed to get frame data"
# define ATTK_F "Failed to load attack frame"

/**
 * @brief Loads all weapon textures and animation frames into memory.
 *
 * Initializes sprite data for each weapon and stores them in the game structure.
 *
 * @param game  Pointer to the main game structure.
 */
void	load_weapons(t_game *game);

/**
 * @brief Draws the currently equipped weapon on the screen.
 *
 * Renders the weapon sprite in first-person view (HUD layer).
 *
 * @param game  Pointer to the main game structure.
 */
void	draw_weapon(t_game *game);

/**
 * @brief Triggers the attack animation for the current weapon.
 *
 * Updates animation state and sets relevant timing flags.
 *
 * @param sprite  Pointer to the weapon or sprite instance.
 */
void	trigger_attack(t_sprite *sprite);

/**
 * @brief Attempts to reload the current weapon.
 *
 * Checks reload conditions and updates the weapon state accordingly.
 *
 * @param sprite  Pointer to the weapon or sprite instance.
 */
void	try_reload(t_sprite *sprite);

/**
 * @brief Builds a complete file path for a weapon texture.
 *
 * Concatenates a base path with an indexed filename (e.g., "media/sprites/hand"+"/1.xpm").
 *
 * @param dst    Destination buffer for the resulting path.
 * @param base   Base directory or file prefix.
 * @param index  Index number to append to the file name.
 */
void	make_path(char *dst, const char *base, int index);

/**
 * @brief Updates the weapon animation state.
 *
 * Advances the current frame of the weapon based on its type and state.
 *
 * @param w        Pointer to the weapon structure.
 * @param w_type   Type of weapon to update (used to select animation set).
 */
void	update_weapon_animation(t_weapon *w, t_weapon_type w_type);

/**
 * @brief Returns the animation frames of the current weapon.
 *
 * Provides access to the weapon’s frame data for rendering.
 *
 * @param w  Pointer to the weapon structure.
 * @return Pointer to the corresponding frame set (t_frames).
 */
t_frames	*get_weapon(t_weapon *w);

#endif