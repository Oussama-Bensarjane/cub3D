#ifndef SPRITES_BONUS_H
# define SPRITES_BONUS_H

# define HAND_ATTACK_FRAMES 3
# define PISTOL_ATTACK_FRAMES 7
# define SHOTGUN_ATTACK_FRAMES 17

void	init_load_weapons(t_game *game);
void	draw_weapon(t_game *game);
void	update_sprites(t_sprite *sprite);
void	trigger_attack(t_sprite *sprite);

void	make_path(char *dst, const char *base, int index);

#endif
