/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/02 16:57:08 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _USE_MATH_DEFINES
#include "cub3d.h"
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

float deg_to_rad(float angle)
{
	return (angle * (float)M_PI / 180.0f);
}

int	start_game(t_game **game)
{
	int				ray;
	float			curr_ang;
	float			alpha;
	t_line			line;
	t_line			draw_line;
	t_grid			t;
	float			dist;
	int				hit;

	printf("Player pos >> x:%f (%d), y: %f (%d), Player angle: %f\n", PLAYER.position.x, (int)(PLAYER.position.x / GRID_SIZE), PLAYER.position.y, (int)(PLAYER.position.y / GRID_SIZE), PLAYER.angle_alpha);
	printf("Size of map >> y:%d, x: %d\n", (*game)->height, (*game)->width);
	// printf("test ft_tan for PI: %f, 2*PI: %f, PI/2:%f \n", ft_tan(180), ft_tan(360), ft_tan(90));
	// if (background_f_c_draw(game))// shoudl call it once!
	// 	return (1);
	ray = 0;
	ft_memset(&t, 0, sizeof(t));
	alpha = 0.0f;
	while (ray < WW)
	{
		printf("FIRST ALTHPA: %f\n", alpha);
		curr_ang = ((float)ray / (float)WW) * (float)(FOV) - (float)(FOV) / 2;
		// TODO:: check later is it possible to use macroses like a PLAYER???
		alpha = PLAYER.angle_alpha - curr_ang;
		if (alpha < 0.0f)
			alpha +=360.0f;
		else if (alpha > 360.0f)
			alpha -=360.0f;
		printf("FIRST ALTHPA after cal: (%f) CURR_ANG (%f)\n\n", alpha, curr_ang);

		//  horizontal intersection
		if (alpha < 180.0f)  // Ray looking up
			line.a.y = floor(PLAYER.position.y / GRID_SIZE) * GRID_SIZE - 0.0001f;
		else  // Ray looking down
			line.a.y = floor(PLAYER.position.y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
		// ΔX = -ΔY / tan(alpha), where ΔY = line.a.y - PLAYER.position.y
		line.a.x = PLAYER.position.x - (line.a.y - PLAYER.position.y) / tanf(deg_to_rad(alpha));
		printf("## line.a: (%f, %f)\n", line.a.x, line.a.y);
		
		// vertical intersection
		if (alpha >= 90.0f && alpha < 270.0f)  // Ray looking left
			line.b.x = floor(PLAYER.position.x / GRID_SIZE) * GRID_SIZE - 0.0001f;
		else  // Ray looking right
			line.b.x = floor(PLAYER.position.x / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
		// ΔY = -ΔX * tan(alpha), where ΔX = line.b.x - PLAYER.position.x
		line.b.y = PLAYER.position.y - (line.b.x - PLAYER.position.x) * tanf(deg_to_rad(alpha));
		printf("## line.b: (%f, %f)\n", line.b.x, line.b.y);
		
		while (1)
		{
			printf("Checking distance: \n");
			if (distance(PLAYER.position, line.a) < distance(PLAYER.position, line.b))
			{
				printf("A < B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				t.x = (int)(line.a.x / GRID_SIZE);
				t.y = (int)(line.a.y / GRID_SIZE);
				printf("after calculation --> A < B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				
				dist = distance(PLAYER.position, line.a);
				hit =  1 + 2 * (alpha < 180.0f); // 1 = North, 3 = South
			}
			else
			{
				printf("A > B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				t.x = (int)(line.b.x / GRID_SIZE);
				t.y = (int)(line.b.y / GRID_SIZE);
				printf("after calculation --> A > B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);

				dist = distance(PLAYER.position, line.b);
				hit = (alpha >= 90.0f && alpha < 270.0f) * 2; // 2 = West, 0 = East
			}
			// printf("---: alpha(%f), t(%d, %d), a(%f, %f), b(%f, %f)\n", alpha, t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
			
			// Check bounds
			if (t.x < 0 || t.x >= (*game)->width || t.y < 0 || t.y >= (*game)->height)
				break ;
			if ((*game)->map[t.y][t.x] == '1')// TODO:: check (our logic) is t.x and t.y real tile's number???
				break ;
			if (distance(PLAYER.position, line.a) < distance(PLAYER.position, line.b))
			{
				// Move to next horizontal grid line
				// ΔX = -ΔY / tan(alpha)
				float step_y = GRID_SIZE * (1 - 2 * (alpha < 180.0f));
				float step_x = -step_y / tanf(deg_to_rad(alpha));
				
				line.a.y += step_y;
				line.a.x += step_x;
			}
			else
			{
				// Move to next vertical grid line
				// ΔY = -ΔX * tan(alpha)
				float step_x = GRID_SIZE * (1 - 2 * (alpha >= 90.0f && alpha < 270.0f));
				float step_y = -step_x * tanf(deg_to_rad(alpha));
				
				line.b.x += step_x;
				line.b.y += step_y;
			}
			printf("+++B: a(%f, %f), b(%f, %f)\n", line.a.x, line.a.y, line.b.x, line.b.y);
		}
		printf("break inside loop   t(%d, %d): ray: %d\n\n\n", t.x, t.y, ray);
		draw_line = (t_line) \
					{{ray, (int)((WH - WW / dist) / 2)}, \
					{ray, (int)((WH + WW / dist) / 2)}, \
					alpha, hit};	
		draw_col(game, draw_line, line);
		
		ray++;
	}
	printf("break main loop \n\n\n");
	
	// mlx_loop((*game)->mlx);        // <<< THIS runs the render/event loop
    // mlx_terminate((*game)->mlx);
	return (0);
}
