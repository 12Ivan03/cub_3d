/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:33:32 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/21 12:37:21 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_rgb(t_rgb rgb, char *msg)
{
	int	result;
	int i;

	i = 0;
	while (i < 3)
	{
		if (rgb.rgb[i] == -1 && rgb.rgb[i] < 256)
			return (error_handler_msg(2, msg));
		i++;
	}
	return (0);
}

int	check_walls(mlx_image_t **walls, char *msg)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (walls[i] == NULL)
			return (error_handler_msg(2, msg));
		i++;
	}
	return (0);
}

int	eval_graph(t_game **game)
{	
	int	result;

	result = 0;
	if (check_rgb((*game)->graph->F, "Missing floor colours"))
		result = 1;
	if (check_rgb((*game)->graph->C, "Missing celing colours"))
		result = 1;
	if (check_walls((*game)->graph->walls, "Missing path for wall"))
		result = 1;
	return (result);
}

// int	eval_graph(t_game **game)
// {	
// 	int	result;

// 	result = 0;
// 	for (int i = 0; i < 3; i++)
// 		if ((*game)->graph->F.rgb[i] == -1 && (*game)->graph->F.rgb[i] < 256)
// 			result = error_handler_msg(2,"Missing floor colours");
// 	for (int i = 0; i < 3; i++)
// 		if ((*game)->graph->C.rgb[i] == -1 && (*game)->graph->C.rgb[i] < 256)
// 			result = error_handler_msg(2,"Missing celing colours");
// 	for (int i = 0; i < 4; i++)
// 		if ((*game)->graph->walls[i] == NULL)
// 			result = error_handler_msg(2,"Missing path for wall");
// 	return (result);
// }
