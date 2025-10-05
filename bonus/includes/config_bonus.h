#ifndef CONFIG_BONUS_H
# define CONFIG_BONUS_H

# define PI 3.141592653589

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define FOV 60.0f
# define SPEED_MAX 15
# define PLAYER_RADIUS 5.0f

# define MINIMAP_RADIUS 8
# define MINIMAP_SCALE 20
# define MINIMAP_OFFSET_X 20
# define MINIMAP_OFFSET_Y 20

# define CLR_FREE_SPACE 0xDCD7C9
# define CLR_WALL 0xF3F2EC
# define CLR_OUTBOUND 0x948979
# define CLR_PLAYER 0xA27B5C
# define CLR_WHITE 0xFFFFFF
# define CLR_GREY 0x808080
# define CLR_BLACK 0x000000

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

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_pointi
{
	int	x;
	int	y;
}	t_pointi;

typedef struct s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef enum e_dir
{
	TEX_NO = 0,
	TEX_SO,
	TEX_WE,
	TEX_EA,
	TEX_MAX
}	t_dir;

typedef struct s_assets
{
	char	player_dir;
	int		floor;
	int		ceiling;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	*textures[4];
	char	**map;
}	t_assets;

typedef struct s_texture
{
	int		width;
	int		height;
	t_img	img;
}	t_texture;

typedef struct s_config
{
	int			floor;
	int			minimap_floor;
	int			ceiling;
	int			map_height;
	int			*map_width;
	char		**map;
	t_texture	textures[4];
}	t_config;

typedef struct s_wall
{
	int		height;
	int		start;
	int		end;
	double	dist;
}	t_wall;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side_hit;
	t_wall	wall;
	double	angle;
	t_point	dir;
	t_point	delta;
	t_point	side;
}	t_ray;

typedef enum e_key
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ROT_LEFT,
	KEY_ROT_RIGHT,
	kEY_MAX
}	t_key;

typedef struct s_player
{
	t_point	p;
	double	angle;
	double	cos_angle;
	double	sin_angle;
	double	angle_speed;
	int		speed;
	bool	key[6];
}	t_player;

typedef struct s_circle
{
	int			radius;
	int			radius2;
	int			radius2_inner;
	t_pointi	center;
	t_pointi	p;
	t_pointi	d;
}	t_circle;

typedef struct s_minimap
{
	t_pointi	p;
	t_pointi	map;
	int			color;
	t_pointi	base;
	t_pointi	target;
	t_circle	circle;
}	t_minimap;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_config	config;
	t_ray		ray;
	t_player	player;
	t_minimap	minimap;
}	t_game;
#endif
