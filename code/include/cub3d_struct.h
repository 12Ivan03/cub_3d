
#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# define HEIGHT_WALL 264
# define WIDTH_WALL 264
# define GRID_SIZE 264
# define INIT_FOV 60
# define HEIGHT_WIN 800
# define WIDTH_WIN 1000
# define MINI_W_WIN 200
# define MINI_H_WIN 200
# define CELL_SIZE 100
# define PROJ_DIST 400
# define MOVE_SPEED 15.0f 
# define NO 90
# define EA 0
# define SO 270
# define WE 180
# define R 0
# define G 1
# define B 2
# define ROTATION_AGNLE 1.5f
# define MINI_MAP_EMPTY_COLOR 0x101000AA
# define MINI_MAP_WALL_COLOR 0x777777FF
# define MINI_MAP_PLAYER_COLOR 0X10F7F0A1 // 0xFF1010FF
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct	s_coordinates
{
	float	x;
	float	y;
}	t_coordinates;

typedef struct	s_pixel
{
	t_coordinates		dot;
	int32_t				color;
}	t_pixel;

typedef struct	s_grid
{
	int	x;
	int	y;
}	t_grid;

typedef struct	s_line
{
	t_coordinates	a;
	t_coordinates	b;
	float			angle;
	int				hit;
}	t_line;

typedef struct	s_player {
	
	float			angle_alpha;
	t_coordinates	position;
	int				x_grid;
	int				y_grid;
} t_player;

typedef struct	s_rgb
{
	int	rgb[3];
} t_rgb;

typedef struct	s_graph
{
	t_rgb		F;
	t_rgb		C;
	mlx_image_t	*walls[4];
	float		proj_dist;
} t_graph;

typedef struct	s_mini_map
{
	int	tile;
} t_mini_map;

typedef struct	s_player_state
{
	t_line	line;
	t_grid	t;
	int		ray;
	float	curr_ang;
	float	step_y;
	float	step_x;
}	t_player_state;

typedef struct	s_draw_line
{
	int				height;
	int				start_y;
	int				end_y;
	float			ratio;
	t_coordinates	pos;
}	t_draw_line;

typedef struct	s_game
{
	mlx_t		*mlx;
	mlx_image_t	*foreground;
	mlx_image_t	*background;
	mlx_image_t	*min_map_img;
	t_mini_map	mini_map_info;
	char		**map;
	t_list		*copy_map;
	t_player	player;
	int			height;
	int			width;
	int 		height_wall;
	int 		width_wall;
	int			fov;
	int			height_window;
	int			width_window;
	float		move_speed;
	double		mouse_y;
	t_graph		*graph;
} t_game;

#endif
