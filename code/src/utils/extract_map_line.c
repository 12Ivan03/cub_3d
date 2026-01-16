/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:37:27 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/16 15:31:12 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	copy_map_to_game_struct(t_game **game, char **line, int fd)
{
	int	check;

	check = 0;
	while ((*line) != NULL && check != 1)
	{
		if (*line[0] == '\n')
			return (error_handler(8));
		check = check_map_line(game, *line);
		free(*line);
		(*line) = get_next_line(fd);
	}
	return (check);
}

int	check_map_line(t_game **game, char *line)
{
	t_list	*tmp_map;
	char	*temp_line;

	temp_line = ft_strtrim(line, "\n");
	if (!temp_line)
		return (error_handler(4));
	tmp_map = ft_lstnew(temp_line);
	ft_lstadd_back(&((*game)->copy_map), tmp_map);
	return (0);
}

int	allocate_and_fill_map_row(t_game **game, int i, t_list *iter)
{
	(*game)->map[i] = (char *)malloc((*game)->width + 1);
	if (!(*game)->map[i])
		return (free_map(&(*game)->map, i), error_handler(4));
	ft_memset((*game)->map[i], ' ', (*game)->width);
	(*game)->map[i][(*game)->width] = '\0';
	ft_memcpy((*game)->map[i], iter->content, ft_strlen(iter->content));
	return (0);
}
