
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

// src

// error handler 
int error_handler(int er);
int error_handler_msg(int er, char *msg);

// free 
void	free_game(t_game **game);

// init
t_game	*init_game(void);

// lib

// parse_map
int	valid_file_name(char *argv[]);
int	valid_file_content(char *argv[], t_game **game);
int	eval_graph(t_game **game);

// utils
int	check_line(char *line, t_game **game);



#endif