/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:16:00 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 12:13:05 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void rezise_window(int32_t width, int32_t heigth, void *param)
{
	t_game **game;
	
	game = (t_game **)param;
	
	// printf("wodth: %d height : %d \n",width, heigth);
	(*game)->height_window = heigth;	
	(*game)->width_window = width;	
	
	// delete old image
	mlx_delete_image((*game)->mlx, (*game)->foreground);
	(*game)->foreground = mlx_new_image((*game)->mlx, WW, WH);	
	mlx_delete_image((*game)->mlx, (*game)->background);
	(*game)->background = mlx_new_image((*game)->mlx, WW, WH);
	mlx_delete_image((*game)->mlx, (*game)->mini_map_image);
	(*game)->mini_map_image = mlx_new_image((*game)->mlx, WIDTH_WIN, HEIGHT_WIN); // or WW , WH

	// put new image
	mlx_image_to_window((*game)->mlx, (*game)->background, 0 ,0);
	mlx_image_to_window((*game)->mlx, (*game)->foreground, 0 ,0);
	mlx_image_to_window((*game)->mlx, (*game)->mini_map_image, 50, 20);

	background_f_c_draw(game);
	start_game(game);
}