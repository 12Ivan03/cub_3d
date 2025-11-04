/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2025/11/04 17:45:43 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_game(t_game **game)
{
	int				ray;
	float			curr_ang;
	float			alpha;
	t_line			line;
	t_line			draw_line;
	t_grid			t;
	float			dist;
	int			hit;

	ray = 0;
	while (ray < WW)
	{
		curr_ang = ray + (FOV / WW);
		alpha = PLAYER.angle_alpha - (FOV / 2) + curr_ang;
		if (alpha < 180)
			line.a.y = roundf(PLAYER.position.y / GRID_SIZE) * GRID_SIZE;
		else
			line.a.y = roundf(PLAYER.position.y / GRID_SIZE + 1) * GRID_SIZE;
		line.a.x = PLAYER.position.x + (PLAYER.position.y - line.a.y) / (float)tan(alpha);
		if (alpha >= 90 && alpha < 270)
			line.b.x = roundf(PLAYER.position.x / GRID_SIZE) * GRID_SIZE;
		else
			line.b.x = roundf(PLAYER.position.x / GRID_SIZE + 1) * GRID_SIZE;
		line.b.y = PLAYER.position.y + (PLAYER.position.x - line.b.x) / (float)tan(alpha);
		while (1)
		{
			if (distance(PLAYER.position, line.a) < distance(PLAYER.position, line.b))
			{
				t.x = (int)(line.a.x / GRID_SIZE);
				t.y = (int)(line.a.y / GRID_SIZE) - (alpha > 179 && alpha < 360);
				dist = distance(PLAYER.position, line.a);
				hit = 1 + 2 * (alpha > 179 && alpha < 360);
			}
			else
			{
				t.x = (int)(line.b.x / GRID_SIZE) - !(alpha > 90 && alpha < 279);
				t.y = (int)(line.b.y / GRID_SIZE);
				dist = distance(PLAYER.position, line.b);
				hit = 2 * !(alpha > 90 && alpha < 279);
			}
			if ((*game)->map[t.x][t.y] == '1')// TODO:: check (our logic) is t.x and t.y real tile's number???
				break ;
			if (distance(PLAYER.position, line.a) < distance(PLAYER.position, line.b))
			{
				line.a.x = line.a.x + GRID_SIZE / tan(alpha);
				line.a.y = line.a.y + GRID_SIZE;
			}
			else
			{
				line.b.x = line.b.x + GRID_SIZE;
				line.b.y = line.b.y + GRID_SIZE * tan(alpha);
			}
		}
		draw_line = (t_line)\
{{ray, (int)((WH - WW / dist) / 2)}, \
{ray, (int)((WH + WW / dist) / 2)}, \
alpha, hit};
		draw_col(game, draw_line, line);
		ray++;
	}
	return (0);
}
