/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:49:52 by aerokhin          #+#    #+#             */
/*   Updated: 2025/11/29 14:56:27 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int put_to_win(t_game **game, t_line line, int colonm_point)
// {

	
// }

int	draw_col(t_game **game, t_line col, t_line line)
{
	(void)game;
	(void)line;
	(void)col;
	int	colonm_point;
	float	colonm_num;

	if (line.hit % 2)
	{
		colonm_num = ((line.a.x - roundf(line.a.x / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		// colonm_point = (int)((colonm_num * (line.hit == 1) + (1 - colonm_num) * (line.hit == 3)) * WIDTH_WALL);
	}
	else
	{
		colonm_num = ((line.b.y - roundf(line.b.y / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		// colonm_point = (int)((colonm_num * (line.hit == 0) + (1 - colonm_num) * (line.hit == 2)) * WIDTH_WALL);
	}
	colonm_point = (int)((colonm_num * (line.hit <= 1) + (1 - colonm_num) * (line.hit >= 2)) * WIDTH_WALL);
	// put_to_win(game, line, colonm_point);
	return 0;
}