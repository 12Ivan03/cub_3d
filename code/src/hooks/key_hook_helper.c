/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:24:18 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/13 12:00:00 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_right(t_game **game)
{
	(*game)->player.angle_alpha -= ROTATION_AGNLE;
	check_angle(&(*game)->player.angle_alpha);
}

void	key_left(t_game **game)
{
	(*game)->player.angle_alpha += ROTATION_AGNLE;
	check_angle(&(*game)->player.angle_alpha);
}

void	key_up(t_game **game)
{
	float	rad;
	float	nx;
	float	ny;

	rad = deg_to_rad((*game)->player.angle_alpha);
	nx = (*game)->player.position.x + cosf(rad) * (*game)->move_speed;
	ny = (*game)->player.position.y - sinf(rad) * (*game)->move_speed;
	if (is_walkable(game, nx, ny))
	{
		(*game)->player.position.x = nx;
		(*game)->player.position.y = ny;
	}
}

void	key_down(t_game **game)
{
	float	rad;
	float	nx;
	float	ny;

	rad = deg_to_rad((*game)->player.angle_alpha);
	nx = (*game)->player.position.x - cosf(rad) * (*game)->move_speed;
	ny = (*game)->player.position.y + sinf(rad) * (*game)->move_speed;
	if (is_walkable(game, nx, ny))
	{
		(*game)->player.position.x = nx;
		(*game)->player.position.y = ny;
	}
}

void	cursor_cb(double xpos, double ypos, void *param)
{
	t_game	**game;

	game = (t_game **)param;
	(void) ypos;
	if ((*game)->mouse_y == -1)
		(*game)->mouse_y = xpos;
	if (mlx_is_mouse_down((*game)->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if ((*game)->mouse_y < xpos || xpos > WIDTH_WIN)
		{
			(*game)->player.angle_alpha -= ROTATION_AGNLE;
			(*game)->mouse_y = xpos;
		}
		else
		{
			(*game)->player.angle_alpha += ROTATION_AGNLE;
			(*game)->mouse_y = xpos;
		}
		check_angle(&(*game)->player.angle_alpha);
	}
}

// void	cursor_cb(double xpos, double ypos, void *param)
// {
// 	t_game	*g = *(t_game **)param;
// 	(void)ypos;
// 	if (!mlx_is_mouse_down(g->mlx, MLX_MOUSE_BUTTON_LEFT))
// 		return;
// 	const double cx = g->mlx->width  / 2.0;
// 	const double cy = g->mlx->height / 2.0;
// 	// dx > 0 means mouse moved right; rotate right/left however your engine defines it
// 	double dx = xpos - cx;
// 	// small deadzone to avoid jitter
// 	if (dx > 0.5)
// 		g->player.angle_alpha -= ROTATION_AGNLE;
// 	else if (dx < -0.5)
// 		g->player.angle_alpha += ROTATION_AGNLE;
// 	check_angle(&g->player.angle_alpha);
// 	// recenter so we never hit screen edges
// 	mlx_set_mouse_pos(g->mlx, (int32_t)cx, (int32_t)cy);
// }