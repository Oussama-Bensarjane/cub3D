#ifndef CONFIG_H
# define CONFIG_H

# define PI 3.141592653589

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define FOV 60.0f
# define SPEED_MAX 15

# if defined(__linux__)
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define LEFT 65361
#  define RIGHT 65363
#  define SPEEDUP 65451
#  define SPEEDDOWN 65453
# elif defined(__APPLE__)
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define LEFT 123
#  define RIGHT 124
#  define SPEEDUP 0x45
#  define SPEEDDOWN 0x4E
# endif

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	side_x;
	double	side_y;
	int		side;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	angle_speed;
	int		speed;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;

}	t_player;

typedef struct s_game
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
