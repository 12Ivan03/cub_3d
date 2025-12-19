/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/19 12:08:22 by ipavlov          ###   ########.fr       */
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
	// float			line.angle;
	t_line			line;
	// t_line			draw_line;
	t_grid			t;
	float			dist;
	// int				hit;

	game = (t_game **)param;
	// printf("Player pos >> x:%f (%d), y: %f (%d), Player angle: %f\n", PLAYER.position.x, (int)(PLAYER.position.x / GRID_SIZE), PLAYER.position.y, (int)(PLAYER.position.y / GRID_SIZE), PLAYER.angle_alpha);
	// printf("Size of map >> y:%d, x: %d\n", (*game)->height, (*game)->width);
	// printf("test ft_tan for PI: %f, 2*PI: %f, PI/2:%f \n", ft_tan(180), ft_tan(360), ft_tan(90));
	// if (background_f_c_draw(game))// shoudl call it once!
	// 	return (1);
	ray = 0;
	ft_memset(&t, 0, sizeof(t));
	ft_bzero((*game)->foreground->pixels, (*game)->foreground->width * (*game)->foreground->height * 4);
	// line.angle = 0.0f;
	while (ray < WW)
	{
		// printf("FIRST ALTHPA: %f\n", line.angle);
		curr_ang = ((float)ray / (float)WW) * (float)(FOV) - (float)(FOV) / 2;
		// TODO:: check later is it possible to use macroses like a PLAYER???
		line.angle = PLAYER.angle_alpha - curr_ang;
		check_angle(&line.angle);
		// printf("FIRST ALTHPA after cal: (%f) CURR_ANG (%f)\n\n", line.angle, curr_ang);

		//  horizontal intersection
		if (line.angle < 180.0f && line.angle > 0.0f)  // Ray looking up
			line.a.y = floor(PLAYER.position.y / GRID_SIZE) * GRID_SIZE - 1.0f;
		else  // Ray looking down
			line.a.y = floor(PLAYER.position.y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
		// ΔX = -ΔY / tan(line.angle), where ΔY = line.a.y - PLAYER.position.y
		line.a.x = PLAYER.position.x - (line.a.y - PLAYER.position.y) / tanf(deg_to_rad(line.angle));
		// printf("## line.a: (%f, %f)\n", line.a.x, line.a.y);
		
		// vertical intersection
		if (line.angle > 90.0f && line.angle < 270.0f)  // Ray looking left
			line.b.x = floorf(PLAYER.position.x / GRID_SIZE) * GRID_SIZE - 1.0f;
		else  // Ray looking right
			line.b.x = floorf(PLAYER.position.x / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
		// ΔY = -ΔX * tan(line.angle), where ΔX = line.b.x - PLAYER.position.x
		line.b.y = PLAYER.position.y - (line.b.x - PLAYER.position.x) * tanf(deg_to_rad(line.angle));
		// printf("## line.b: (%f, %f)\n", line.b.x, line.b.y);
		
		while (1)
		{
			// printf("Checking distance: \n");
			if (distance(PLAYER.position, line.a) <= distance(PLAYER.position, line.b))
			{
				// printf("A < B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				t.x = (int)(line.a.x / GRID_SIZE);
				t.y = (int)(line.a.y / GRID_SIZE);
				// printf("after calculation --> A < B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				
				dist = distance(PLAYER.position, line.a);
				line.hit =  1 + 2 * (line.angle <= 180.0f && line.angle >= 0.0f); // 1 = North, 3 = South
			}
			else
			{
				// printf("A > B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				t.x = (int)(line.b.x / GRID_SIZE);
				t.y = (int)(line.b.y / GRID_SIZE);
				// printf("after calculation --> A > B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);

				dist = distance(PLAYER.position, line.b);
				line.hit = (line.angle >= 90.0f && line.angle <= 270.0f) * 2; // 2 = West, 0 = East
			}
			
			// Check bounds
			if (t.x < 0 || t.x >= (*game)->width || t.y < 0 || t.y >= (*game)->height)
			{
				// printf("map[%d][%d]\n",t.y, t.x );
				// printf("---: line.angle(%f), t(%d, %d), a(%f, %f), b(%f, %f)\n", line.angle, t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				break ;
			}
			if ((*game)->map[t.y][t.x] == '1')// TODO:: check (our logic) is t.x and t.y real tile's number???
			{
				// printf("map[%d][%d]\n",t.y, t.x );
				// printf("---: line.angle(%f), t(%d, %d), a(%f, %f), b(%f, %f)\n", line.angle, t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				break ;
			}
			if (distance(PLAYER.position, line.a) < distance(PLAYER.position, line.b))
			{
				// Move to next horizontal grid line
				// ΔX = -ΔY / tan(line.angle)
				float step_y = GRID_SIZE * (1 - 2 * (line.angle < 180.0f));
				float step_x = -step_y / tanf(deg_to_rad(line.angle));
				
				line.a.y += step_y;
				line.a.x += step_x;
			}
			else
			{
				// Move to next vertical grid line
				// ΔY = -ΔX * tan(line.angle)
				float step_x = GRID_SIZE * (1 - 2 * (line.angle >= 90.0f && line.angle < 270.0f));
				float step_y = -step_x * tanf(deg_to_rad(line.angle));
				
				line.b.x += step_x;
				line.b.y += step_y;
				// if (step_y < 0)
					// printf("-------------- %f -------------\n", step_y);
			}
			// printf("+++B: a(%f, %f), b(%f, %f)\n", line.a.x, line.a.y, line.b.x, line.b.y);
		}
		// printf("ray: %d, hit: %d \n",  ray, line.hit);

		draw_col(game, line, ray, curr_ang);
		
		ray++;
	}
	// exit(0);
	// printf("break main loop \n\n\n");
	
	// mlx_loop((*game)->mlx);        // <<< THIS runs the render/event loop
    // mlx_terminate((*game)->mlx);
	// return (0);
}
