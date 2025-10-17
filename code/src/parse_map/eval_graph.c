/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:33:32 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/17 17:34:25 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	eval_graph(t_game **game)
{
	// (void)game;
	for (int i = 0; i < 3; i++)
		if ((*game)->graph->F.rgb[i] == -1 && (*game)->graph->F.rgb[i] < 256)
			return (error_handler_msg(2,"Missing floor colours"));
	for (int i = 0; i < 3; i++)
		if ((*game)->graph->C.rgb[i] == -1 && (*game)->graph->C.rgb[i] < 256)
			return (error_handler_msg(2,"Missing celing colours"));
	for (int i = 0; i < 4; i++)
		if ((*game)->graph->walls[i] == NULL)
			return (error_handler_msg(2,"Missing path for wall"));
			
	return 1;
}