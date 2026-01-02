/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:24:18 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 16:39:21 by ipavlov          ###   ########.fr       */
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
	float rad = deg_to_rad((*game)->player.angle_alpha);
    float nx = (*game)->player.position.x + cosf(rad) * (*game)->move_speed;
    float ny = (*game)->player.position.y - sinf(rad) * (*game)->move_speed;

    if (is_walkable(game, nx, ny))
    {
        (*game)->player.position.x = nx;
        (*game)->player.position.y = ny;
    }
}

void	key_down(t_game **game)
{
	float rad = deg_to_rad((*game)->player.angle_alpha);
    float nx = (*game)->player.position.x - cosf(rad) * (*game)->move_speed;
    float ny = (*game)->player.position.y + sinf(rad) * (*game)->move_speed;

    if (is_walkable(game, nx, ny))
    {
        (*game)->player.position.x = nx;
        (*game)->player.position.y = ny;
    }
}	

void cursor_cb(double xpos, double ypos, void *param)
{
	t_game **game;

	game = (t_game **)param;
	(void) ypos;
	if ((*game)->mouse_y == -1)
		(*game)->mouse_y = xpos;
	if (mlx_is_mouse_down((*game)->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if ((*game)->mouse_y < xpos) {
			(*game)->player.angle_alpha -= ROTATION_AGNLE;
			(*game)->mouse_y = xpos;
		} else {
			(*game)->player.angle_alpha += ROTATION_AGNLE;
			(*game)->mouse_y = xpos;
		}
		check_angle(&(*game)->player.angle_alpha);
	}
}