/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:40:35 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 12:14:22 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	read_process_map(t_game **game)
{
	int		i;
	t_list	*iter;

	i = -1;
	iter = (*game)->copy_map;
	(*game)->height = count_height(game);
	(*game)->width = count_width(game);
	(*game)->map = (char **)malloc((*game)->height * sizeof(char *));
	if (!(*game)->map)
		return (1);
	while (++i < (*game)->height)
	{
		(*game)->map[i] = (char *)ft_calloc(((*game)->width + 1), 1);
		if (!(*game)->map[i])
			return (free_map(&(*game)->map, i), error_handler(4));
		ft_strlcat((*game)->map[i], (char *)iter->content, (*game)->width + 1);
		if (set_position(game, i))
			return (error_handler(8));
		if (eval_map_line((*game)->map[i]))
			return (free_map(&(*game)->map, i + 1), error_handler(8));
		iter = iter->next;
	}
	check_mini_map(game);
	return (0);
}
