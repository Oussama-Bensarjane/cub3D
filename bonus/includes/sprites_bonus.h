#ifndef SPRITES_BONUS_H
# define SPRITES_BONUS_H

void	init_load_weapons(t_game *game);
void	draw_weapon(t_game *game);
void	update_sprites(t_sprite *sprite);
void	trigger_attack(t_sprite *sprite);

void	make_path(char *dst, const char *base, int index);

#endif