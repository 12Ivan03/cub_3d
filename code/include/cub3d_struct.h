
#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

# define HEIGHT_WALL 64;
# define WIDTH_WALL 64;
# define FOV 60;
# define HEIGHT_WINDOWS 800;
# define WIDTH_WINDOWS 1024;
# define CELL_SIZE 100;
# define IS_EMPTY_SPACE(c) ((c) == ' ' || (c) == '\t')
# define NO 0;
# define EA 1;
# define SO 2;
# define WE 3;
# define R 0;
# define G 1;
# define B 2;


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
	int rgb[3];
} t_rgb;

typedef struct s_graph
{
	t_rgb F;
	t_rgb C;
	mlx_image_t *walls[4];
} t_graph;

typedef struct s_game
{
	mlx_t	*mlx;
	int		*map;
	int		height;
	int		width;
	int		fov;
	int		height_window;
	int		width_window;
	t_graph	*graph;
	


} t_game;

#endif