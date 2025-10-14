
#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

# define HEIGHT_WALL 64;
# define WIDTH_WALL 64;
# define FOV 60;
# define HEIGHT_WINDOWS 800;
# define WIDTH_WINDOWS 1024;
# define CELL_SIZE 100;

typedef struct s_coordinates
{
	int	x;
	int	y;
} t_coordinates;

typedef struct s_player {

	int angle;
	t_coordinates position;

} t_player;

typedef struct s_rgb
{
	int r;
	int g;
	int b;
} t_rgb;

typedef struct s_graph
{
	t_rgb F;
	t_rgb C;
	mlx_texture_t *no_wall;
	mlx_texture_t *so_wall;
	mlx_texture_t *we_wall;
	mlx_texture_t *ea_wall;
} t_graph;

typedef struct s_game
{
	mlx_t *mlx;
	int *map;
	int	height;
	int width;
	int fov;
	int	height_window;
	int width_window;
	t_graph *graph;
	


} t_game;

#endif