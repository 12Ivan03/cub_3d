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
	// printf("(*game)->width: %d\n", (*game)->width );
	(*game)->map = (char **)malloc((*game)->height * sizeof(char *));
	if (!(*game)->map)
		return (1);
	while (++i < (*game)->height)
	{
		// printf("iter->content   -> %s\n",(char *)iter->content);
		(*game)->map[i] = (char *)malloc((*game)->width + 1);
		if (!(*game)->map[i])
			return (free_map(&(*game)->map, i), error_handler(4));
		ft_memset((*game)->map[i], ' ', (*game)->width);
		(*game)->map[i][(*game)->width] = '\0';
		ft_memcpy((*game)->map[i], iter->content, ft_strlen(iter->content));
		// printf("(*game)->map[i] -> >%s<\n", (*game)->map[i]);
		// put in extract_map_line -> in utils
		// if (convert_map_in_two_d_arr())
		// 	return (error_handler(4)) <- remove the error from malloc check...
		if (set_position(game, i))
			return (error_handler(8));
		if (eval_map_line((*game)->map[i]))
			return (free_map(&(*game)->map, i + 1), error_handler(8));
		iter = iter->next;
	}
	check_mini_map(game);
	return (0);
}
