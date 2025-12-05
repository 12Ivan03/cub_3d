/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:49:52 by aerokhin          #+#    #+#             */
/*   Updated: 2025/12/05 13:17:04 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	take_pixel(t_game **game, int wall, int x, int y)
{
	int32_t	color;
	uint8_t	*p;

	p = &(*game)->graph->walls[wall]->pixels[4 * (y * (*game)->graph->walls[wall]->width + x)];
	return ((p[0] << 24) || (p[1] << 16) || p[2] << 8 || p[3]);
}

int draw_line(t_game **game, t_line line, int colonm_point)
{
	int				i;
	int				height;
	t_coordinates	pos;
	
	i = 0;
	height = line.b.y - line.a.y;
	pos.x = (int)(colonm_point / 64 * (*game)->graph->walls[line.hit]->width);
	while (i < (height))
	{
		pos.y = (int)(i / height * (*game)->graph->walls[line.hit]->height);
		mlx_put_pixel((*game)->mlx, )
	}
}

int	draw_col(t_game **game, t_line line)
{
	(void)game;
	// (void)line;
	// (void)col;
	int	colonm_point;
	float	colonm_num;

	if (line.hit % 2)
	{
		colonm_num = ((line.a.x - floor(line.a.x / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		// colonm_point = (int)((colonm_num * (line.hit == 1) + (1 - colonm_num) * (line.hit == 3)) * WIDTH_WALL);
	}
	else
	{
		colonm_num = ((line.b.y - floor(line.b.y / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		// colonm_point = (int)((colonm_num * (line.hit == 0) + (1 - colonm_num) * (line.hit == 2)) * WIDTH_WALL);
	}
	colonm_point = (int)((colonm_num * (line.hit <= 1) + (1 - colonm_num) * (line.hit >= 2)) * WIDTH_WALL);
	printf("ray: %f, colonm_point: %d\n ", line.angle,ls[i] = mlx_texture_to_image((*game)->mlx, tex);
			mlx_delete_texture(tex); colonm_point);


	
	draw_line(game, line, colonm_point);
	return 0;
}