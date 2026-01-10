/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 13:07:57 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	plr_init(t_player_state *plr, t_game **game)
{
	plr->ray = 0;
	plr->curr_ang = 0;
	plr->step_y = 0;
	plr->step_x = 0;
	plr->line.a.x = 0;
	plr->line.a.y = 0;
	plr->line.b.x = 0;
	plr->line.b.y = 0;
	plr->line.angle = 0;
	plr->line.hit = 0;
	plr->t.x = 0;
	plr->t.y = 0;
	ft_bzero((*game)->foreground->pixels, (*game)->foreground->width * \
(*game)->foreground->height * 4);
	ft_bzero((*game)->min_map_img->pixels, (*game)->min_map_img->width * \
(*game)->min_map_img->height * sizeof(uint32_t));
};
