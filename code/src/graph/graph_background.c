/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_background.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:07:10 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 12:28:11 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	put_color(t_rgb rgb);

int	background_f_c_draw(t_game **game)
{
	uint32_t	ceil_col;
	uint32_t	floor_col;
	uint32_t	col;
	int			y;
	int			x;

	if (!(*game)->background)
		return (error_handler(7));
	ceil_col = put_color((*game)->graph->C);
	floor_col = put_color((*game)->graph->F);
	y = 0;
	while (y < (*game)->height_window)
	{
		if (y < (*game)->height_window / 2)
			col = ceil_col;
		else
			col = floor_col;
		x = -1;
		while (++x < (*game)->width_window)
			mlx_put_pixel((*game)->background, x, y, col);
		y++;
	}
	return (0);
}

uint32_t	put_color(t_rgb rgb)
{
	uint32_t	tmp;

	tmp = (((uint32_t)(rgb.rgb[0]) << 24) | ((uint32_t)(rgb.rgb[1]) << 16) | \
((uint32_t)(rgb.rgb[2]) << 8) | 0xFF);
	return (tmp);
}
