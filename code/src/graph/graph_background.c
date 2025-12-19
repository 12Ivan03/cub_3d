/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_background.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:07:10 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/12 13:15:13 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int background_f_c_draw(t_game **game)
{
	// mlx_image_t *img;
	uint32_t ceil_col;
    uint32_t floor_col;

	// img = (*game)->background;
	if (!(*game)->background)
		return (error_handler(7));
	
	ceil_col = (((uint32_t)((*game)->graph->C.rgb[0]) << 24) |
                 ((uint32_t)((*game)->graph->C.rgb[1]) << 16) |
                 ((uint32_t)((*game)->graph->C.rgb[2]) << 8) |
				0xFF);
    floor_col = (((uint32_t)((*game)->graph->F.rgb[0]) << 24) |
                  ((uint32_t)((*game)->graph->F.rgb[1]) << 16) |
                  ((uint32_t)((*game)->graph->F.rgb[2]) << 8) | 0xFF);

	// printf("Ceiling: %d, %d, %d\n", (*game)->graph->C.rgb[0], 
					// (*game)->graph->C.rgb[1], 
					// (*game)->graph->C.rgb[2]);
	// printf("Floor: %d, %d, %d\n", (*game)->graph->F.rgb[0], 
					// (*game)->graph->F.rgb[1], 
					// (*game)->graph->F.rgb[2]);
	int y = 0;
	while(y < WH)
	{
		uint32_t col = (y < WH / 2) ? ceil_col : floor_col;
		int x = 0;
		while(x < WW)
		{
			mlx_put_pixel((*game)->background, x, y, col);
			// printf("%d, %d: %d, \n", x, y, col);
			// if(x == 0 || x == WIDTH_WINDOWS - 1)
			// 	printf("-%d ", x);

			x++;
		}
		// printf("(%d), ", y);
		y++;
    }
	// printf("\nHELL");
	// write(1, "\nHELL\n", 6);
	// printf("\n Window:%d, %d", (*game)->width_window, (*game)->height_window);
	
	return (0);
}