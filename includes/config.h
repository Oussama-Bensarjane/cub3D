#ifndef CONFIG_H
#define CONFIG_H

# define PI 3.141592653589

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define FOV_D 60.0f
# define FOV_R (PI / 3)
# define SPEED 1

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

typedef struct	s_player
{
	float	x;
	float	y;
	float	angle;
	float	angle_speed;
	int		speed;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;

}	t_player;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	char		**map;
}	t_game;
#endif
