/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:46:07 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 17:15:21 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	eval_cell(t_game **game, int x, int y, int dx, int dy)// TODO: should be only 4 values!!!
{
	if ((y == 0 || x == 0) && (*game)->map[x][y] == '0') // TODO:  || == '2'
		return (1);
	if (dx == 1)
		if ((x > 0) && (*game)->map[x][y] == '0') // TODO:  || == '2'
			if ((*game)->map[x - dx][y - dy] == ' ' || x == (*game)->height - 1)
				return (1);
	if (dy == 1)
		if (y > 0 && (*game)->map[x][y] == '0') // TODO:  || == '2'
			if ((*game)->map[x - dx][y - dy] == ' ' || \
				(*game)->map[x + dx][y + dy] == ' ' || \
				(*game)->map[x + dx][y + dy] == '\0')
				return (1);
	return (0);
}

int	validate_map(t_game **game)
{
	int i; 
	int j;

	i = 0;
	while (i < (*game)->height)
	{
		j = 0;
		while (j < (*game)->width)
		{
			if (eval_cell(game, i, j, 0, 1))
				return (1);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < (*game)->width)
	{
		j = 0;
		while (j < (*game)->height)
		{
			if (eval_cell(game, j, i, 1, 0))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_struct(t_game **game)
{
	if ((*game)->player.position.x == -1)
		return (error_handler_msg(5, "a player position"));
	if ((*game)->graph->C.rgb[0] == -1 || (*game)->graph->F.rgb[0] == -1)
		return (error_handler_msg(5, "colors"));
	return (0);
}
