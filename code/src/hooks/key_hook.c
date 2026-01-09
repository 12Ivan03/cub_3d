/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:24:18 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 18:08:07 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_tile_wall(t_game **game, int tx, int ty)
{
	if (tx < 0 || tx > (*game)->width || ty < 0 || ty > (*game)->height)
		return (0);
	return ((*game)->map[ty][tx] != '1');
}

int	is_walkable(t_game **game, float x, float y)
{
	int		left;
	int		right;
	int		top;
	int		bottom;
	float	r;

	r = MOVE_SPEED / 1.41f + 2.0f;
	left = (int)((x - r) / GRID_SIZE);
	right = (int)((x + r) / GRID_SIZE);
	top = (int)((y - r) / GRID_SIZE);
	bottom = (int)((y + r) / GRID_SIZE);
	if (!is_tile_wall(game, left, top))
		return (0);
	if (!is_tile_wall(game, right, top))
		return (0);
	if (!is_tile_wall(game, left, bottom))
		return (0);
	if (!is_tile_wall(game, right, bottom))
		return (0);
	return (1);
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
