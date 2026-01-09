/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:37:27 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 12:19:58 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	copy_map_to_game_struct(t_game **game, char **line, int fd)
{
	int	check;

	check = 0;
	while ((*line) != NULL)
	{
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
	return (1);
}
