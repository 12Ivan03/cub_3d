
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include "cub3d_struct.h" 
# include "math.h"


// src

// error handler 
int error_handler(int er);
int error_handler_msg(int er, char *msg);

// free 
void	free_game(t_game **game);
void	free_map(char ***arr, int i);

// init
t_game	*init_game(void);

// lib

// hooks
void	key_stroks(mlx_key_data_t keydata, void *params);
void rezise_window(int32_t width, int32_t heigth, void *param);

// parse_file
int	valid_file_name(char *argv, char *str);
int	read_file_content(char *argv[], t_game **game);
int	eval_graph(t_game **game);
//----> map proccesing
int	handle_map(t_game **game);

// utils
int	check_line(char *line, t_game **game);
int	check_map_line(t_game **game, char *line);
int	copy_map_to_game_struct(t_game **game, char **line, int fd);

// math
float	projection_distance(t_game **game);
float	distance(t_coordinates a, t_coordinates b);
void	check_angle(float *angle);
float	deg_to_rad(float angle);

// graph
int	draw_col(t_game **game, t_line line, int ray_x, float curr_ang);
int background_f_c_draw(t_game **game);


// game
void	start_game(void *param);


#endif