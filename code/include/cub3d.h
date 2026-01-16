/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:18:59 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/16 11:27:40 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int		error_handler(int er);
int		error_handler_msg(int er, char *msg);

// free 
void	free_game(t_game **game);
void	free_map(char ***arr, int i);

// init
t_game	*init_game(void);
void	plr_init(t_player_state *plr, t_game **game);

// hooks
void	key_stroks(mlx_key_data_t keydata, void *params);
void	rezise_window(int32_t width, int32_t heigth, void *param);
void	cursor_cb(double xpos, double ypos, void *param);
void	cursor_cb(double xpos, double ypos, void *param);
void	key_down(t_game **game);
void	key_up(t_game **game);
void	key_left(t_game **game);
void	key_right(t_game **game);
int		is_walkable(t_game **game, float x, float y);

// parse_file
int		valid_file_name(char *argv, char *str);
int		parse_file_content(char *argv[], t_game **game);
int		eval_graph(t_game **game);
int		open_file(char *file);
int		read_validate_direc_fc(int fd, t_game **game);
int		validate_map(t_game **game);
int		validate_struct(t_game **game);
int		validate_struct(t_game **game);
int		validate_map(t_game **game);
int		eval_cell(t_game **game, int x, int y);
int		read_process_map(t_game **game);
int		allocate_and_fill_map_row(t_game **game, int i, t_list *iter);

// utils
int		parse_and_config_line(char *line, t_game **game);
int		check_map_line(t_game **game, char *line);
int		copy_map_to_game_struct(t_game **game, char **line, int fd);
int		celling_floow_texture(t_game **game, char *extract, int i);
int		wall_texture(t_game **game, char *extract, int i);
int		eval_map_line(char *arr);
int		set_position(t_game **game, int y);
int		find_start_position(t_game **game, int i, int j);
int		count_height(t_game **game);
int		count_width(t_game **game);

// math
float	projection_distance(t_game **game);
float	distance(t_coordinates a, t_coordinates b);
void	check_angle(float *angle);
float	deg_to_rad(float angle);

// graph
int		draw_col(t_game **game, t_player_state *plr);
int		background_f_c_draw(t_game **game);

// mini map
void	draw_mini_map(t_game **game);
void	mm_fill_rect(t_game **game, t_pixel corditate, int size);
void	draw_background_mini_map(t_game **game);
void	check_mini_map(t_game **game);

// game
void	start_game(void *param);

#endif
