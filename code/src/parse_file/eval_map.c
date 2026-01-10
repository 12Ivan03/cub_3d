/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:46:07 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 16:38:44 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	eval_cell(t_game **game, int x, int y, int d)
{
	if ((y == 0 || x == 0) && (*game)->map[x][y] == '0')
		return (1);
	if (d == 0)
	{
		if ((x > 0) && (*game)->map[x][y] == '0')
			if ((*game)->map[x][y - 1] == ' ' || x == (*game)->height - 1 \
|| (*game)->map[x][y + 1] == ' ' || (*game)->map[x][y + 1] == '\0')
				return (1);
	}
	else
		if (y > 0 && (*game)->map[x][y] == '0')
			if ((*game)->map[x - 1][y] == ' ' || \
(*game)->map[x + 1][y] == ' ' || (*game)->map[x + 1][y] == '\0')
				return (1);
	return (0);
}

int	scan_map(t_game **game, int outer, int inner, int cell)
{
	int	i;
	int	j;

	i = 0;
	while (i < outer)
	{
		j = 0;
		while (j < inner)
		{
			if (cell == 0)
			{
				if (eval_cell(game, i, j, cell))
					return (1);
			}
			else 
			{
				if (eval_cell(game, j, i, cell))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(t_game **game)
{
	if (scan_map(game, (*game)->height, (*game)->width, 0))
		return (1);
	if (scan_map(game, (*game)->width, (*game)->height, 1))
		return (1);
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
