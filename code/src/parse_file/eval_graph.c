/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:33:32 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/20 14:37:45 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	eval_graph(t_game **game)
{	
	int	result;

	result = 1;
	for (int i = 0; i < 3; i++)
		if ((*game)->graph->F.rgb[i] == -1 && (*game)->graph->F.rgb[i] < 256)
			result = error_handler_msg(2,"Missing floor colours");
	for (int i = 0; i < 3; i++)
		if ((*game)->graph->C.rgb[i] == -1 && (*game)->graph->C.rgb[i] < 256)
			result = error_handler_msg(2,"Missing celing colours");
	for (int i = 0; i < 4; i++)
		if ((*game)->graph->walls[i] == NULL)
			result = error_handler_msg(2,"Missing path for wall");
	return (result);
}

	// printf("C rgb0 --> %d\n",(*game)->graph->C.rgb[0]);
	// printf("C rgb1 --> %d\n",(*game)->graph->C.rgb[1]);
	// printf("C rgb2 --> %d\n",(*game)->graph->C.rgb[2]);

	// printf("F rgb0 --> %d\n",(*game)->graph->F.rgb[0]);
	// printf("F rgb1 --> %d\n",(*game)->graph->F.rgb[1]);
	// printf("F rgb2 --> %d\n",(*game)->graph->F.rgb[2]);
	// // printf((*game)->graph->F.rgb);
	// // printf("(*game)->graph->walls[0]--> %p\n",(*game)->graph->walls[0]);
	// for (int i = 0; i < 4; i++) {
	// 	mlx_image_t *img = (*game)->graph->walls[i];
		
	// 	if (img == NULL) {
	// 		printf("walls[0] is NULL\n");
	// 	} else {
	// 		printf("walls[%d] is NOT NULL, ptr=%p\n", i, (void*)img);
	// 	}
	// }