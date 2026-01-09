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

int	validate_map(t_game **game)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*game)->height)
	{
		j = 0;
		while (j < (*game)->width)
		{
			if (eval_cell(game, i, j, 0))
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
			if (eval_cell(game, j, i, 1))
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
