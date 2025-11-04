/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2025/11/04 14:26:26 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_game(t_game **game)
{
	// (void)game;
	int				ray;
	float			curr_ang;
	float			alpha;
	t_coordinates	a;
	t_coordinates	b;
	t_grid			t;
	// int				exit_loop;
	
	ray = 0;
	// exit_loop = 0;
	while (ray < (*game)->width_window)
	{
		curr_ang = ray + (FOV / WW);
		alpha = PLAYER.angle_alpha - (FOV / 2) + curr_ang;
		if (alpha < 180)
			a.y = roundf(PLAYER.position.y / WL_H) * WL_H;
		else
			a.y = roundf(PLAYER.position.y / WL_H + 1) * WL_H;
		a.x = PLAYER.position.x + (PLAYER.position.y - a.y) / (float)tan(alpha);
		if (alpha >= 90 && alpha < 270)
			b.x = roundf(PLAYER.position.x / WL_W) * WL_W;
		else
			b.x = roundf(PLAYER.position.x / WL_W + 1) * WL_W;
		b.y = PLAYER.position.y + (PLAYER.position.x - b.x) / (float)tan(alpha);
		while (1)
		{
			{
				/* code */
			}
			
			if (distance(PLAYER.position, a) < distance(PLAYER.position, b))
			{
				t.x = (int)(a.x / WL_W);
				t.y = (int)(a.y / WL_H);
			}
			else
			{
				t.x = (int)(b.x / WL_W);
				t.y = (int)(b.y / WL_H);
			}
			if ((*game)->map[t.x][t.y] = '1')
				break; // ????????
		
		ray++;
	}
	return 0;
}