/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/13 11:12:08 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _USE_MATH_DEFINES
#include "cub3d.h"
#include <math.h>

void	ray_hit_points(t_game **game, t_player_state *plr);
void	compute_ray_angle(t_game **game, t_player_state *plr);
void	select_ray_hit(t_game **game, t_player_state *plr);
void	advance_ray_intersection(t_game **game, t_player_state *plr);

void	start_game(void *param)
{
	t_game			**game;
	t_player_state	plr;

	game = (t_game **)param;
	plr_init(&plr, game);
	draw_background_mini_map(game);
	while (plr.ray < (*game)->width_window)
	{
		compute_ray_angle(game, &plr);
		ray_hit_points(game, &plr);
		while (1)
		{
			select_ray_hit(game, &plr);
			if (plr.t.x < 0 || plr.t.x >= (*game)->width || \
plr.t.y < 0 || plr.t.y >= (*game)->height)
				break ;
			if ((*game)->map[plr.t.y][plr.t.x] == '1')
				break ;
			advance_ray_intersection(game, &plr);
		}
		draw_col(game, &plr);
		draw_mini_map(game);
		plr.ray++;
	}
}

void	ray_hit_points(t_game **game, t_player_state *plr)
{
	int		grid;
	float	plr_y;
	float	plr_x;
	float	tang_plr_ang;

	grid = GRID_SIZE;
	plr_y = (*game)->player.position.y;
	plr_x = (*game)->player.position.x;
	tang_plr_ang = tanf(deg_to_rad(plr->line.angle));
	if (plr->line.angle < 180.0f && plr->line.angle > 0.0f)
		plr->line.a.y = floor(plr_y / grid) * grid;
	else
		plr->line.a.y = floor(plr_y / grid) * grid + grid;
	plr->line.a.x = plr_x - (plr->line.a.y - plr_y) / tang_plr_ang;
	if (plr->line.angle > 90.0f && plr->line.angle < 270.0f)
		plr->line.b.x = floorf(plr_x / grid) * grid;
	else
		plr->line.b.x = floorf(plr_x / grid) * grid + grid;
	plr->line.b.y = plr_y - (plr->line.b.x - plr_x) * tang_plr_ang;
}

void	compute_ray_angle(t_game **game, t_player_state *plr)
{
	plr->curr_ang = ((float)plr->ray / (float)(*game)->width_window) * \
(float)((*game)->fov) - (float)((*game)->fov) / 2;
	plr->line.angle = (*game)->player.angle_alpha - plr->curr_ang;
	check_angle(&plr->line.angle);
}

void	select_ray_hit(t_game **game, t_player_state *plr)
{
	float	dist_to_horz;
	float	dist_to_vert;

	dist_to_horz = distance((*game)->player.position, plr->line.a);
	dist_to_vert = distance((*game)->player.position, plr->line.b);
	if (dist_to_horz <= dist_to_vert)
	{
		plr->t.x = (int)floorf(plr->line.a.x / GRID_SIZE);
		plr->t.y = (int)floorf(plr->line.a.y / GRID_SIZE);
		if (plr->line.angle < 180.0f && plr->line.angle > 0.0f)
			plr->t.y -= 1;
		plr->line.hit = 1 + 2 * \
(plr->line.angle < 180.0f && plr->line.angle > 0.0f);
	}
	else
	{
		plr->t.x = (int)floorf(plr->line.b.x / GRID_SIZE);
		plr->t.y = (int)floorf(plr->line.b.y / GRID_SIZE);
		if (plr->line.angle > 90.0f && plr->line.angle < 270.0f)
			plr->t.x -= 1;
		plr->line.hit = \
(plr->line.angle > 90.0f && plr->line.angle < 270.0f) * 2;
	}
}

void	advance_ray_intersection(t_game **game, t_player_state *plr)
{
	float	dist_to_horz;
	float	dist_to_vert;
	float	ang;

	dist_to_horz = distance((*game)->player.position, plr->line.a);
	dist_to_vert = distance((*game)->player.position, plr->line.b);
	ang = plr->line.angle;
	if (dist_to_horz < dist_to_vert)
	{
		plr->step_y = GRID_SIZE * (1 - 2 * (ang < 180.0f));
		plr->step_x = -plr->step_y / tanf(deg_to_rad(ang));
		plr->line.a.y += plr->step_y;
		plr->line.a.x += plr->step_x;
	}
	else
	{
		plr->step_x = GRID_SIZE * (1 - 2 * (ang >= 90.0f && ang < 270.0f));
		plr->step_y = -plr->step_x * tanf(deg_to_rad(ang));
		plr->line.b.x += plr->step_x;
		plr->line.b.y += plr->step_y;
	}
}
