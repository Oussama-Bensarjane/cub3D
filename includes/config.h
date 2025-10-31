#ifndef CONFIG_H
# define CONFIG_H

# define PI 3.141592653589

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define FOV 60.0f
# define PLAYER_RADIUS 5.0f
# define SPEED_MAX 15
# define PLAYER_ANGLE_SPEED 0.05f
# define MOUSE_SENSITIVITY 0.005f

# define MINIMAP_RADIUS 8
# define MINIMAP_OFFSET_X 20
# define MINIMAP_OFFSET_Y 20

# define CLR_FREE_SPACE 0xDCD7C9
# define CLR_WALL 0xF3F2EC
# define CLR_OUTBOUND 0x948979
# define CLR_PLAYER 0xA27B5C
# define CLR_DOOR 0x86B0BD
# define CLR_DOOR_AREA 0xB6CEB4
# define CLR_BLACK 0x000000

# define TEX_DOOR_PATH "media/textures/door.xpm"
# define TEX_HELP_PATH "media/textures/help.xpm"
# define SPRITES_PATH "media/sprites" 
# define MAX_FRAMES 20

# if defined (__linux__)

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define SPEEDUP 65451
# define SPEEDDOWN 65453
# define SPACE 32
# define NUM_1 49
# define NUM_2 50
# define NUM_3 51
# define E 101
# define V 118
# define H 104
# define R 114

# elif defined (__APPLE__)

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define SPEEDUP 69
# define SPEEDDOWN 78
# define SPACE 49
# define NUM_1 18
# define NUM_2 19
# define NUM_3 20
# define E 14
# define V 9
# define H 4
# define R 15

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
	TEX_NO,
	TEX_SO,
	TEX_WE,
	TEX_EA,
	TEX_DOOR,
	TEX_HELP,
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
	int		nbr_line;
	int		fd;
	char	*textures[6];
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
	t_texture	textures[6];
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
	int		door_hit;
	t_wall	wall;
	double	angle;
	t_point	dir;
	t_point	delta;
	t_point	side;
}	t_ray;

typedef enum e_key
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ROT_LEFT,
	KEY_ROT_RIGHT,
	KEY_V,
	KEY_H,
	KEY_R,
	kEY_MAX
}	t_key;

typedef struct s_player
{
	t_point	p;
	double	angle;
	double	cos_angle;
	double	sin_angle;
	int		speed;
	bool	key[9];
}	t_player;

typedef enum e_weapon_type
{
	W_HAND,
	W_PISTOL,
	W_SHUTGUN,
	W_MAX
}	t_weapon_type;

typedef enum e_weapon_state
{
	WS_IDLE,
	WS_ATTACK,
	WS_RELOAD,
	WS_IDLE_RELOAD
}	t_weapon_state;

typedef struct s_frames
{
	t_img	imgs[MAX_FRAMES];
	int		count;
	int		current;
	int		width;
	int		height;
}	t_frames;

typedef struct s_weapon
{
	t_frames		idle;
	t_frames		idle_reload;
	t_frames		attack;
	t_frames		reload;
	int				frame_timer;
	int				frame_delay;
	int				reload_timer;
	int				reload_delay;
	int				bullets;
	t_weapon_state	state;
}	t_weapon;

typedef struct s_sprite
{
	t_weapon	weapons[3];
	int			current;
}	t_sprite;

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
	int			scale;
	int			radius;
	int			radius2;
	t_pointi	p;
	t_pointi	pacman;
	t_pointi	map;
	t_pointi	base;
	t_pointi	target;
	t_circle	circle;
}	t_minimap;

typedef struct s_door
{
	int		id;
	int		x;
	int		y;
	int		is_open;
}	t_door;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_config	config;
	t_ray		ray;
	t_player	player;
	t_sprite	sprite;
	t_list		*doors;
	t_minimap	minimap;
}	t_game;
#endif
