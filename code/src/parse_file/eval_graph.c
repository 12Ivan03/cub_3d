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

int	eval_graph(t_game **game)
{	
	int	result;

	result = 0;
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
