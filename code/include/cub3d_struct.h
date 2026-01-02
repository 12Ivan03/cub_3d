
#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

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
# define MOVE_SPEED 10.0f 
# define NO 90
# define EA 0
# define SO 270
# define WE 180
# define R 0
# define G 1
# define B 2
# define ROTATION_AGNLE 0.5f
# define MINI_MAP_EMPTY_COLOR 0x101000AA
# define MINI_MAP_WALL_COLOR 0x777777FF



# define IS_EMPTY_SPACE(c) ((c) == ' ' || (c) == '\t')
# define FOV (*game)->fov
# define WW (*game)->width_window
# define WH (*game)->height_window
# define PLAYER (*game)->player
# define WL_H (*game)->height_wall
# define WL_W (*game)->width_wall

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif


typedef struct s_coordinates
{
	float	x;
	float	y;
}	t_coordinates;

typedef struct s_pixel
{
	t_coordinates		dot;
	int32_t				color;
}	t_pixel;

typedef struct	s_grid
{
	int	x;
	int	y;
}	t_grid;

typedef struct s_line
{
	t_coordinates	a;
	t_coordinates	b;
	float			angle;
	int				hit;
}	t_line;

typedef struct s_player {
	
	float angle_alpha;
	t_coordinates position;
	int x_grid; // x/64 = floor(res); 
	int y_grid; // y/64 = floor(res);

} t_player;

typedef struct s_rgb
{
	int rgb[3];
} t_rgb;

typedef struct s_graph
{
	t_rgb 		F;
	t_rgb 		C;
	mlx_image_t	*walls[4];
	float		proj_dist;
} t_graph;

typedef struct s_mini_map
{
	int tile;
} t_mini_map;


typedef struct s_game
{
	mlx_t	*mlx;
	mlx_image_t *foreground;
	mlx_image_t *background;
	mlx_image_t *mini_map_image;
	t_mini_map	mini_map_info;
	char	**map;
	t_list	*copy_map;
	t_player player;
	int		height;
	int		width;
	int 	height_wall;
	int 	width_wall;
	int		fov;
	int		height_window;
	int		width_window;
	float	move_speed;
	double	mouse_y;
	t_graph	*graph;

} t_game;

#endif