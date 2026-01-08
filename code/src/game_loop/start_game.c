/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/08 15:24:43 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _USE_MATH_DEFINES
#include "cub3d.h"
#include <math.h>

void	start_game(void *param)
{
	t_game **game;
	int				ray;
	float			curr_ang;
	t_line			line;
	t_grid			t;
	// float			dist;

	game = (t_game **)param;
	ray = 0;

	ft_memset(&t, 0, sizeof(t));
	ft_bzero((*game)->foreground->pixels, (*game)->foreground->width * (*game)->foreground->height * 4);
	ft_bzero((*game)->mini_map_image->pixels, (*game)->mini_map_image->width * (*game)->mini_map_image->height * sizeof(uint32_t));
	draw_background_mini_map(game); // draws the mini map on the window.

	while (ray < WW)
	{
		curr_ang = ((float)ray / (float)WW) * (float)(FOV) - (float)(FOV) / 2;
		line.angle = PLAYER.angle_alpha - curr_ang;
		check_angle(&line.angle);

		//  horizontal intersection
		if (line.angle < 180.0f && line.angle > 0.0f)  // Ray looking up
			line.a.y = floor(PLAYER.position.y / GRID_SIZE) * GRID_SIZE;
		else  // Ray looking down
			line.a.y = floor(PLAYER.position.y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
		line.a.x = PLAYER.position.x - (line.a.y - PLAYER.position.y) / tanf(deg_to_rad(line.angle));
		
		// vertical intersection
		if (line.angle > 90.0f && line.angle < 270.0f)  // Ray looking left
			line.b.x = floorf(PLAYER.position.x / GRID_SIZE) * GRID_SIZE;
		else  // Ray looking right
			line.b.x = floorf(PLAYER.position.x / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
		line.b.y = PLAYER.position.y - (line.b.x - PLAYER.position.x) * tanf(deg_to_rad(line.angle));
		
		while (1)
		{
			if (distance(PLAYER.position, line.a) <= distance(PLAYER.position, line.b))
			{
				t.x = (int)floorf(line.a.x / GRID_SIZE);
				t.y = (int)floorf(line.a.y / GRID_SIZE);
				// Looking up: check cell above (subtract 1 from y)
				if (line.angle < 180.0f && line.angle > 0.0f)
					t.y -= 1;
				line.hit = 1 + 2 * (line.angle < 180.0f && line.angle > 0.0f); // 1 = North, 3 = South
			}
			else
			{
				t.x = (int)floorf(line.b.x / GRID_SIZE);
				t.y = (int)floorf(line.b.y / GRID_SIZE);
				// Looking left: check cell to the left (subtract 1 from x)
				if (line.angle > 90.0f && line.angle < 270.0f)
					t.x -= 1;
				line.hit = (line.angle > 90.0f && line.angle < 270.0f) * 2; // 2 = West, 0 = East
			}
			
			// Check bounds
			if (t.x < 0 || t.x >= (*game)->width || t.y < 0 || t.y >= (*game)->height)
				break ;
			if ((*game)->map[t.y][t.x] == '1')// TODO:: check (our logic) is t.x and t.y real tile's number???
				break ;
			if (distance(PLAYER.position, line.a) < distance(PLAYER.position, line.b))
			{
				// Move to next horizontal grid line
				float step_y = GRID_SIZE * (1 - 2 * (line.angle < 180.0f));
				float step_x = -step_y / tanf(deg_to_rad(line.angle));
				
				line.a.y += step_y;
				line.a.x += step_x;
			}
			else
			{
				// Move to next vertical grid line
				float step_x = GRID_SIZE * (1 - 2 * (line.angle >= 90.0f && line.angle < 270.0f));
				float step_y = -step_x * tanf(deg_to_rad(line.angle));
				
				line.b.x += step_x;
				line.b.y += step_y;
			}
		}

		draw_col(game, line, ray, curr_ang);
		draw_mini_map(game); // draw the payer  on the mini map
		
		ray++;
	}
	// exit(0);
}
