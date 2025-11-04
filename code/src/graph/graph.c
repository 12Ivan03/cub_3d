/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:49:52 by aerokhin          #+#    #+#             */
/*   Updated: 2025/11/04 18:02:51 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_col(t_game **game, t_line col, t_line line)
{
	(void)game;
	(void)line;
	int	colonm;
	float	colonm_num;

	if (line.hit % 2)
	{
		colonm_num = ((line.a.x - roundf(line.a.x / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		colonm = (int)((colonm_num * (line.hit == 1) + (1 - colonm_num) * (line.hit == 3)) * WIDTH_WALL);
	}
	else
	{
		colonm_num = ((line.b.y - roundf(line.b.y / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		colonm = (int)((colonm_num * (line.hit == 0) + (1 - colonm_num) * (line.hit == 2)) * WIDTH_WALL);
	}

	return 0;
}