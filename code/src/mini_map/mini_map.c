/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 12:38:10 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_mini_map(t_game **game)
{
	int mini_h;
	int mini_w;

	mini_h = (*game)->height * (*game)->mini_map_info.tile;
	mini_w = (*game)->height * (*game)->mini_map_info.tile;
	if (mini_h > HEIGHT_WIN - 50 || mini_w > WIDTH_WIN - 50)
		(*game)->mini_map_info.tile = 0;
}

void	mm_fill_rect(t_game **game, t_pixel corditate, int size)
{
	int32_t c = corditate.color;
	int yy;
	int xx;

	yy = 0;
	while (yy < size)
	{
		xx = 0;
		while (xx < size)
		{
			mlx_put_pixel((*game)->mini_map_image, \
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
		return;
	cor.dot.x = (int)(((*game)->player.position.x / (float)GRID_SIZE) * tile) - 2;
	cor.dot.y = (int)(((*game)->player.position.y / (float)GRID_SIZE) * tile) - 2;
	cor.color = MINI_MAP_PLAYER_COLOR;
	mm_fill_rect(game, cor, 5); 
	angle_rad = deg_to_rad((*game)->player.angle_alpha);
	k = 0;
	while (k < 30)
	{
		pixel.dot.x = cor.dot.x + (int)(cosf(angle_rad) * k) + 2;
		pixel.dot.y = cor.dot.y - (int)(sinf(angle_rad) * k) + 2;
		if (pixel.dot.x >= 0 && pixel.dot.x < (int)(*game)->mini_map_image->width && \
			pixel.dot.y >= 0 && pixel.dot.y < (int)(*game)->mini_map_image->height)
			mlx_put_pixel((*game)->mini_map_image, pixel.dot.x, pixel.dot.y, MINI_MAP_PLAYER_COLOR);
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
		return;
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

// void    draw_mini_map(t_game **game)
// {
//     // int i;
//     // int j;
//     const int tile_size = 8;
//     int img_w = (int)(*game)->mini_map_image->width;
//     int img_h = (int)(*game)->mini_map_image->height;
//     int player_mm_x = (int)(((*game)->player.position.x / (float)GRID_SIZE) * tile_size);
//     int player_mm_y = (int)(((*game)->player.position.y / (float)GRID_SIZE) * tile_size);
//     float start_px = (float)player_mm_x - img_w / 2.0f;
//     float start_py = (float)player_mm_y - img_h / 2.0f;
//     int start_tile_x = (int)floorf(start_px / (float)tile_size);
//     int start_tile_y = (int)floorf(start_py / (float)tile_size);
//     int end_tile_x = (int)ceilf((start_px + img_w) / (float)tile_size);
//     int end_tile_y = (int)ceilf((start_py + img_h) / (float)tile_size);
//     if (start_tile_x < 0) start_tile_x = 0;
//     if (start_tile_y < 0) start_tile_y = 0;
//     if (end_tile_x > (*game)->width - 1) end_tile_x = (*game)->width - 1;
//     if (end_tile_y > (*game)->height - 1) end_tile_y = (*game)->height - 1;
//     for (int ty = start_tile_y; ty <= end_tile_y; ty++)
//     {
//         for (int tx = start_tile_x; tx <= end_tile_x; tx++)
//         {
//             int px = (int)(tx * tile_size - start_px);
//             int py = (int)(ty * tile_size - start_py);
//             if (px + tile_size < 0 || py + tile_size < 0 || px >= img_w || py >= img_h)
//                 continue;
//             char cell = (*game)->map[ty][tx];
//             if (cell == '1')
//                 mm_fill_rect((*game)->mini_map_image, px, py, tile_size, tile_size, 0x777777FF);
//         }
//     }
//     /* draw player centered in the mini-map image */
//     int center_x = img_w / 2;
//     int center_y = img_h / 2;
//     mm_fill_rect((*game)->mini_map_image, center_x - 2, center_y - 2, 5, 5, 0xFF0000FF);
//     /* direction line from center */
//     float angle_rad = (*game)->player.angle_alpha * M_PI / 180.0f;
//     for (int k = 0; k < 40; k++)
//     {
//         int lx = center_x + (int)(cosf(angle_rad) * k);
//         int ly = center_y - (int)(sinf(angle_rad) * k);
//         if (lx >= 0 && lx < img_w && ly >= 0 && ly < img_h)
//             mlx_put_pixel((*game)->mini_map_image, lx, ly, 0xFF0000FF);
//     }
// }