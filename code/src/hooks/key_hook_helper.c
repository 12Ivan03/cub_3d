/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:24:18 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/20 12:38:57 by ipavlov          ###   ########.fr       */
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
	double	cursor_x;
	double	cursor_y;
	double	middle_place;

	cursor_x = WIDTH_WALL / 2.0;
	cursor_y = WIDTH_WALL / 2.0;
	middle_place = xpos - cursor_x;
	game = (t_game **)param;
	(void) ypos;
	if ((*game)->mouse_y == -1)
		(*game)->mouse_y = xpos;
	if (mlx_is_mouse_down((*game)->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (middle_place > 0.5)
			(*game)->player.angle_alpha -= ROTATION_AGNLE;
		else
			(*game)->player.angle_alpha += ROTATION_AGNLE;
		check_angle(&(*game)->player.angle_alpha);
		mlx_set_mouse_pos((*game)->mlx, (int32_t)cursor_x, (int32_t)cursor_y);
	}
}
