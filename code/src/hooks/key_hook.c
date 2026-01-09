/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:24:18 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 12:03:37 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(t_game **game, float x, float y)
{
	int	tx;
	int	ty;

	tx = (int)(x / GRID_SIZE);
	ty = (int)(y / GRID_SIZE);
	if (tx < 0 || tx > (*game)->width || ty < 0 || ty > (*game)->height)
		return (0);
	return ((*game)->map[ty][tx] != '1');
}

void	close_game(t_game **game)
{
	free_game(game);
	exit(0);
}

void	key_stroks(mlx_key_data_t keydata, void *params)
{
	t_game	**game;

	(void) keydata;
	game = (t_game **)params;
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_UP) || \
mlx_is_key_down((*game)->mlx, MLX_KEY_W))
		key_up(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_DOWN) || \
mlx_is_key_down((*game)->mlx, MLX_KEY_S))
		key_down(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_LEFT) || \
mlx_is_key_down((*game)->mlx, MLX_KEY_A))
		key_left(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_RIGHT) || \
mlx_is_key_down((*game)->mlx, MLX_KEY_D))
		key_right(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_ESCAPE))
		close_game(game);
}
