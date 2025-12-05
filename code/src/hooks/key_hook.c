/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:24:18 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/05 15:25:51 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_game(t_game **game)
{
	free_game(game);
	exit(0);
}


void	key_right(t_game **game)
{
	(*game)->player.angle_alpha -= ROTATION_AGNLE;
	check_angle(&(*game)->player.angle_alpha);
	start_game(game);
}

void	key_left(t_game **game)
{
	(*game)->player.angle_alpha += ROTATION_AGNLE;
	check_angle(&(*game)->player.angle_alpha);
	start_game(game);
}
// UP AND DOWN
void	key_up(t_game **game)
{
	(*game)->player.angle_alpha -=ROTATION_AGNLE;
	check_angle(&(*game)->player.angle_alpha);
	start_game(game);
}

void	key_down(t_game **game)
{
	(*game)->player.angle_alpha +=ROTATION_AGNLE;
	check_angle(&(*game)->player.angle_alpha);
	start_game(game);
}	



void	key_stroks(mlx_key_data_t keydata, void *params)
{
	(void) params;
	(void) keydata;
	t_game **game;

	game = (t_game **)params;

	if (mlx_is_key_down((*game)->mlx, MLX_KEY_UP))
		key_up(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_DOWN))
		key_down(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_LEFT))
		key_left(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_RIGHT))
		key_right(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_ESCAPE))
		close_game(game);
}
