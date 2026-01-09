/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 12:12:11 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_mini_map(t_game **game)
{
	int	mini_h;
	int	mini_w;

	mini_h = (*game)->height * (*game)->mini_map_info.tile;
	mini_w = (*game)->height * (*game)->mini_map_info.tile;
	if (mini_h > HEIGHT_WIN - 50 || mini_w > WIDTH_WIN - 50)
		(*game)->mini_map_info.tile = 0;
}

void	mm_fill_rect(t_game **game, t_pixel corditate, int size)
{
	int32_t	c;
	int		yy;
	int		xx;

	c = corditate.color;
	yy = 0;
	while (yy < size)
	{
		xx = 0;
		while (xx < size)
		{
			mlx_put_pixel((*game)->min_map_img, \
corditate.dot.x + xx, corditate.dot.y + yy, c);
			xx++;
		}
		yy++;
	}
}

void	draw_mini_map(t_game **game)
{
	float	tile;
	t_pixel	cor;
	t_pixel	pixel;
	int		k;
	float	angle_rad;

	tile = (float)(*game)->mini_map_info.tile;
	if (tile <= 0)
		return ;
	cor.dot.x = (int)(((*game)->player.position.x / \
(float)GRID_SIZE) * tile) - 2;
	cor.dot.y = (int)(((*game)->player.position.y / \
(float)GRID_SIZE) * tile) - 2;
	cor.color = MINI_MAP_PLAYER_COLOR;
	mm_fill_rect(game, cor, 5);
	angle_rad = deg_to_rad((*game)->player.angle_alpha);
	k = 0;
	while (k < 30)
	{
		pixel.dot.x = cor.dot.x + (int)(cosf(angle_rad) * k) + 2;
		pixel.dot.y = cor.dot.y - (int)(sinf(angle_rad) * k) + 2;
		if (pixel.dot.x >= 0 && pixel.dot.x < (int)(*game)->min_map_img->width \
&& pixel.dot.y >= 0 && pixel.dot.y < (int)(*game)->min_map_img->height)
			mlx_put_pixel((*game)->min_map_img, pixel.dot.x, pixel.dot.y, \
MINI_MAP_PLAYER_COLOR);
		k++;
	}
}

void	draw_background_mini_map(t_game **game)
{
	int		i;
	int		j;
	char	cell;
	t_pixel	cordinate;

	if ((*game)->mini_map_info.tile <= 0)
		return ;
	i = 0;
	while (i < (*game)->height)
	{
		j = 0;
		while (j < (*game)->width)
		{
			cordinate.dot.x = j * (*game)->mini_map_info.tile;
			cordinate.dot.y = i * (*game)->mini_map_info.tile;
			cell = (*game)->map[i][j];
			if (cell == '1')
				cordinate.color = MINI_MAP_WALL_COLOR;
			else
				cordinate.color = MINI_MAP_EMPTY_COLOR;
			mm_fill_rect(game, cordinate, (*game)->mini_map_info.tile);
			j++;
		}
		i++;
	}
}
