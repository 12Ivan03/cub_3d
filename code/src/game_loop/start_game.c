/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/02 16:51:39 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifndef M_PI
# define M_PI 3.141526
#endif

float ft_tan(float angle)
{
	return (tanf(angle * (float)M_PI / 180.0f));
}

// float ft_tan(float angle)
// {
// 	float rad;
// 	rad = angle * (float)M_PI / 180.0f;
// 	return tanf(rad);
// }

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

	printf("Player pos >> x:%f (%d), y: %f (%d)\n", PLAYER.position.x, (int)(PLAYER.position.x / GRID_SIZE), PLAYER.position.y, (int)(PLAYER.position.y / GRID_SIZE));
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

		//  horizontal
		if (alpha < 180.0f)
			line.a.y = floor(PLAYER.position.y / GRID_SIZE) * GRID_SIZE;
		else
			line.a.y = floor(PLAYER.position.y / GRID_SIZE + 1.0f) * GRID_SIZE;
		line.a.x = PLAYER.position.x - (-PLAYER.position.y + line.a.y) / (float)ft_tan(alpha);
		printf("## line.a: (%f, %f)\n", line.a.x, line.a.y);
		
		// vertival
		if (alpha >= 90.0f && alpha < 270.0f)
			line.b.x = floor(PLAYER.position.x / GRID_SIZE) * GRID_SIZE;
		else
			line.b.x = floor(PLAYER.position.x / GRID_SIZE + 1.0f) * GRID_SIZE;
		line.b.y = PLAYER.position.y - (-PLAYER.position.x + line.b.x) / (float)ft_tan(alpha);
		printf("## line.b: (%f, %f)\n", line.b.x, line.b.y);
		
		while (1)
		{
			printf("Checking distance: \n");
			if (distance(PLAYER.position, line.a) < distance(PLAYER.position, line.b))
			{
				printf("A < B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				t.x = (int)(line.a.x / GRID_SIZE);
				t.y = (int)(line.a.y / GRID_SIZE) - (alpha > 179.9f && alpha < 360.0f);
				printf("after calculation --> A < B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
				
				dist = distance(PLAYER.position, line.a);
				hit = 1 + 2 * (alpha > 179.9f && alpha < 360.0f); // hit == 1 or 3
			}
			else
			{
				printf("A > B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);

				t.x = (int)(line.b.x / GRID_SIZE) - !(alpha > 90.0f && alpha < 270.0f);

				t.y = (int)(line.b.y / GRID_SIZE);
				printf("after calculation --> A > B: t(%d, %d), a(%f, %f), b(%f, %f)\n", t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);

				dist = distance(PLAYER.position, line.b);
				hit = 2 * !(alpha > 90.0f && alpha < 270.0f); // hit == 0 or 2
			}
			printf("map[%d][%d]\n",t.y, t.x );
			// printf("---: alpha(%f), t(%d, %d), a(%f, %f), b(%f, %f)\n", alpha, t.x, t.y, line.a.x, line.a.y, line.b.x, line.b.y);
			if ((*game)->map[t.y][t.x] == '1')// TODO:: check (our logic) is t.x and t.y real tile's number???
				break ;
			if (distance(PLAYER.position, line.a) < distance(PLAYER.position, line.b))
			{
				line.a.x = line.a.x + GRID_SIZE / ft_tan(alpha);
				line.a.y = line.a.y + GRID_SIZE;
			}
			else
			{
				line.b.x = line.b.x + GRID_SIZE;
				line.b.y = line.b.y + GRID_SIZE * ft_tan(alpha);
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
