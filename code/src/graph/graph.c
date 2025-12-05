/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:49:52 by aerokhin          #+#    #+#             */
/*   Updated: 2025/12/05 17:30:33 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	take_pixel(t_game **game, int wall, int x, int y)
{
	// int32_t	color;
	uint8_t	*p;

	p = &(*game)->graph->walls[wall]->pixels[4 * (y * (*game)->graph->walls[wall]->width + x)];
	return (((int32_t)p[0] << 24) | (int32_t)(p[1] << 16) | (int32_t)p[2] << 8 | (int32_t)p[3]);
}

void draw_line(t_game **game, t_line line, int colonm_point, float dist)
{
	int				i;
	int				height;
	t_coordinates	pos;
	
	i = 0;
	height = (int)(HEIGHT_WALL / floor(dist) * (*game)->graph->proj_dist);
	printf("Height: %d\n", height);
	pos.x = (int)(colonm_point / 64 * (*game)->graph->walls[line.hit]->width);
	printf("\n\n(*game)->graph->walls[line.hit]->width =====> %d ; pos.x = %f ; height = %d\n\n", (*game)->graph->walls[line.hit]->width, pos.x, height);
	if (height < 0 || height > HEIGHT_WINDOWS) {
		
		printf("\n\n(*game)->graph->walls[line.hit]->width =====> %d ; pos.x = %f ; height = %d\n\n", (*game)->graph->walls[line.hit]->width, pos.x, height);
		
		ft_putstr_fd("no no no no... what are you doing ? hmmm\n",1);
		exit(1);
	}
	while (i < (height))
	{
		pos.y = (int)(i / height * (*game)->graph->walls[line.hit]->height);
		mlx_put_pixel((*game)->foreground, (WH - height) / 2 + pos.y, colonm_point, take_pixel(game, line.hit, pos.x, pos.y));
		i++;
	}

}

int	draw_col(t_game **game, t_line line)
{
	(void)game;
	// (void)line;
	// (void)col;
	int	colonm_point;
	float	colonm_num;
	float	dist;

	if (line.hit % 2)
	{
		colonm_num = ((line.a.x - floor(line.a.x / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		dist = distance(PLAYER.position, line.a);
		// colonm_point = (int)((colonm_num * (line.hit == 1) + (1 - colonm_num) * (line.hit == 3)) * WIDTH_WALL);
	}
	else
	{
		colonm_num = ((line.b.y - floor(line.b.y / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		dist = distance(PLAYER.position, line.b);
		// colonm_point = (int)((colonm_num * (line.hit == 0) + (1 - colonm_num) * (line.hit == 2)) * WIDTH_WALL);
	}
	colonm_point = (int)((colonm_num * (line.hit <= 1) + (1 - colonm_num) * (line.hit >= 2)) * WIDTH_WALL);
	printf("ray: %f, colonm_point: %d\n ", line.angle, colonm_point);
	// printf("ray: %f, colonm_point: %d\n ", line.b.y, line.a.x);


	
	draw_line(game, line, colonm_point, dist);
	return 0;
}