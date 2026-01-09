/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:49:52 by aerokhin          #+#    #+#             */
/*   Updated: 2026/01/09 12:28:50 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	take_pixel(t_game **game, int wall, int x, int y)
{
	uint8_t	*p;

	p = &(*game)->graph->walls[wall]->\
pixels[4 * (y * (*game)->graph->walls[wall]->width + x)];
	return (((int32_t)p[0] << 24) | (int32_t)(p[1] << 16) | \
(int32_t)p[2] << 8 | (int32_t)p[3]);
}

void	draw_line(t_game **game, t_line line, int colonm_point, float dist, int ray_x)
{
	int				i;
	int				height;
	int				start_y;
	int				end_y;
	float			ratio;
	t_coordinates	pos;

	if (dist < 0.001f)
		dist = 0.001f;
	height = (int)(HEIGHT_WALL / dist * (*game)->graph->proj_dist);
	pos.x = colonm_point;
	if (pos.x < 0)
		pos.x = 0;
	if (pos.x >= (*game)->graph->walls[line.hit]->width)
		pos.x = (*game)->graph->walls[line.hit]->width - 1;
	start_y = (WH - height) / 2;
	end_y = (WH + height) / 2;
	if (start_y < 0)
		start_y = 0;
	if (end_y > WH)
		end_y = WH;
	i = start_y;
	while (i < end_y)
	{
		ratio = (float)(i - (WH - height) / 2) / (float)height;
		pos.y = (int)(ratio * (*game)->graph->walls[line.hit]->height);
		if (pos.y < 0)
			pos.y = 0;
		if (pos.y >= (*game)->graph->walls[line.hit]->height)
			pos.y = (*game)->graph->walls[line.hit]->height - 1;
		mlx_put_pixel((*game)->foreground, ray_x, i, \
take_pixel(game, line.hit, pos.x, pos.y));
		i++;
	}
}

int	draw_col(t_game **game, t_line line, int ray_x, float curr_ang)
{
	int		colonm_point;
	float	colonm_num;
	float	dist;

	if (line.hit % 2 != 0)
	{
		colonm_num = ((line.a.x - floor((line.a.x + 0.00f) / GRID_SIZE) \
* GRID_SIZE) / GRID_SIZE);
		dist = distance(PLAYER.position, line.a);
	}
	else
	{
		colonm_num = ((line.b.y - floor((line.b.y + 0.00f) / GRID_SIZE) \
* GRID_SIZE) / GRID_SIZE);
		dist = distance(PLAYER.position, line.b);
	}
	dist = dist * cosf(deg_to_rad(curr_ang));
	colonm_point = floor((colonm_num * (line.hit <= 1) + (1 - colonm_num) \
* (line.hit >= 2)) * (*game)->graph->walls[line.hit]->width);
	if (colonm_point < 0)
		colonm_point = 0;
	if (colonm_point >= (int)(*game)->graph->walls[line.hit]->width)
		colonm_point = (int)(*game)->graph->walls[line.hit]->width - 1;
	draw_line(game, line, colonm_point, dist, ray_x);
	return (0);
}
