/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_background.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:07:10 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 14:20:50 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int background_f_c_draw(t_game **game)
{
	uint32_t ceil_col;
    uint32_t floor_col;
	int y;
	int x;

	if (!(*game)->background)
		return (error_handler(7));
	
	ceil_col = (((uint32_t)((*game)->graph->C.rgb[0]) << 24) |
                 ((uint32_t)((*game)->graph->C.rgb[1]) << 16) |
                 ((uint32_t)((*game)->graph->C.rgb[2]) << 8) |
				0xFF);
    floor_col = (((uint32_t)((*game)->graph->F.rgb[0]) << 24) |
                  ((uint32_t)((*game)->graph->F.rgb[1]) << 16) |
                  ((uint32_t)((*game)->graph->F.rgb[2]) << 8) | 0xFF);
	y = 0;
	while(y < WH)
	{
		uint32_t col = (y < WH / 2) ? ceil_col : floor_col;
		x = 0;
		while(x < WW)
		{
			mlx_put_pixel((*game)->background, x, y, col);
			x++;
		}
		y++;
    }
	
	return (0);
}