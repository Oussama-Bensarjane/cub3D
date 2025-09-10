#ifndef CONFIG_H
#define CONFIG_H

# define PI 3.141592653589

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

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
