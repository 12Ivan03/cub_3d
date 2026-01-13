/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:49:52 by aerokhin          #+#    #+#             */
/*   Updated: 2026/01/13 11:13:37 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_wall_slice(t_game **game, t_draw_line *dl, \
t_player_state *plr, int colonm_point)
{
	dl->pos.x = colonm_point;
	if (dl->pos.x < 0)
		dl->pos.x = 0;
	if (dl->pos.x >= (*game)->graph->walls[plr->line.hit]->width)
		dl->pos.x = (*game)->graph->walls[plr->line.hit]->width - 1;
	dl->start_y = ((*game)->height_window - dl->height) / 2;
	dl->end_y = ((*game)->height_window + dl->height) / 2;
	if (dl->start_y < 0)
		dl->start_y = 0;
	if (dl->end_y > (*game)->height_window)
		dl->end_y = (*game)->height_window;
}

int32_t	take_pixel(t_game **game, int wall, int x, int y)
{
	uint8_t	*p;

	p = &(*game)->graph->walls[wall]->\
pixels[4 * (y * (*game)->graph->walls[wall]->width + x)];
	return (((int32_t)p[0] << 24) | (int32_t)(p[1] << 16) | \
(int32_t)p[2] << 8 | (int32_t)p[3]);
}

void	draw_line(t_game **game, t_player_state *plr, int clm_point, float dist)
{
	t_draw_line		dl;
	int				i;
	int				w_min_h;

	w_min_h = ((*game)->height_window - dl.height);
	if (dist < 0.001f)
		dist = 0.001f;
	dl.height = (int)(HEIGHT_WALL / dist * (*game)->graph->proj_dist);
	compute_wall_slice(game, &dl, plr, clm_point);
	i = dl.start_y;
	while (i < dl.end_y)
	{
		dl.ratio = (float)(i - w_min_h / 2) / (float)dl.height;
		dl.pos.y = (int)(dl.ratio * \
(*game)->graph->walls[plr->line.hit]->height);
		if (dl.pos.y < 0)
			dl.pos.y = 0;
		if (dl.pos.y >= (*game)->graph->walls[plr->line.hit]->height)
			dl.pos.y = (*game)->graph->walls[plr->line.hit]->height - 1;
		mlx_put_pixel((*game)->foreground, plr->ray, i, \
take_pixel(game, plr->line.hit, dl.pos.x, dl.pos.y));
		i++;
	}
}

int	draw_col(t_game **game, t_player_state *plr)
{
	int		colonm_point;
	float	colonm_num;
	float	dist;

	if (plr->line.hit % 2 != 0)
	{
		colonm_num = ((plr->line.a.x - \
floor((plr->line.a.x + 0.00f) / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		dist = distance((*game)->player.position, plr->line.a);
	}
	else
	{
		colonm_num = ((plr->line.b.y - \
floor((plr->line.b.y + 0.00f) / GRID_SIZE) * GRID_SIZE) / GRID_SIZE);
		dist = distance((*game)->player.position, plr->line.b);
	}
	dist = dist * cosf(deg_to_rad(plr->curr_ang));
	colonm_point = floor((colonm_num * (plr->line.hit <= 1) + (1 - colonm_num) \
* (plr->line.hit >= 2)) * (*game)->graph->walls[plr->line.hit]->width);
	if (colonm_point < 0)
		colonm_point = 0;
	if (colonm_point >= (int)(*game)->graph->walls[plr->line.hit]->width)
		colonm_point = (int)(*game)->graph->walls[plr->line.hit]->width - 1;
	draw_line(game, plr, colonm_point, dist);
	return (0);
}
