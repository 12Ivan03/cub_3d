/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:40:35 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 16:44:32 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	count_width(t_game **game)
{
	int		counter;
	t_list	*tmp;
	int		len;

	counter = 0;
	tmp = (*game)->copy_map;
	while (tmp != NULL)
	{
		len = ft_strlen((char *)(tmp->content));
		if (counter <= len)
			counter = len;
		tmp = tmp->next;
	}
	return (counter);
}

int	count_height(t_game **game)
{
	return (ft_lstsize((*game)->copy_map));
}

int	find_start_position(t_game **game, int i, int j)
{
	while (j < (*game)->width && (*game)->map[i][j] != 0)
	{
		if (ft_strchr("NWSE", (*game)->map[i][j]))
			return (j);
		j++;
	}
	return (-1);
}

int	set_position(t_game **game, int y)
{
	char	angle;
	int		x;

	x = find_start_position(game, y, 0);
	if (find_start_position(game, y, x + 1) != -1)
		return (free_map(&(*game)->map, y + 1), 1);
	if (x != -1)
	{
		if ((*game)->player.position.x != -1 || \
(*game)->player.position.y != -1)
			return (free_map(&(*game)->map, y + 1), 1);
		(*game)->player.position.x = (x + 0.5) * GRID_SIZE;
		(*game)->player.position.y = (y + 0.5) * GRID_SIZE;
		angle = (*game)->map[y][x];
		(*game)->player.angle_alpha = \
EA * (angle == 'E') + NO * (angle == 'N') + \
WE * (angle == 'W') + SO * (angle == 'S');
		(*game)->map[y][x] = '0';
	}
	return (0);
}

int	eval_map_line(char *arr)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(arr);
	while (j < len && arr[j] != 0)
	{
		if (!ft_strchr("NWSE10 ", arr[j]))
			return (1);
		j++;
	}
	return (0);
}
