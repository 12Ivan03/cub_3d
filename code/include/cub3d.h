
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "../lib/get_next_line"

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
	mlx_texture_t no_wall;
	mlx_texture_t so_wall;
	mlx_texture_t we_wall;
	mlx_texture_t ea_wall;

} t_graph;

typedef struct s_game {

	mlx_t mlx;
	int *map;
	t_graph graph;

	
} t_game;

// error handler 
int error_handler(int er);

// lib


// parse_map
int	valid_file(char *argv[]);
int	valid_file_content(char *argv[]);

// src

// utils

#endif